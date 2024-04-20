#include "AssetsLoader.hpp"

namespace SPN
{
    AssetsLoader::AssetsLoader()
    {}

    std::pair<std::string, LoadedTextureFile> AssetsLoader::LoadTextureFile(const std::string& name, const std::string& filepath, const TextureType type, const bool& flipUV, const bool& SRGB)
    {  
        // Données déjà récupérable à l'appel de la fonction
        LoadedTextureFile loaded_texture;
        loaded_texture.filepath = filepath;
        loaded_texture.srgb = SRGB;
        loaded_texture.texture_type = type;

        // Partie chargement de la texture dans la structure
        stbi_set_flip_vertically_on_load_thread(flipUV);
        loaded_texture.image_data.data = stbi_load(filepath.c_str(), &(loaded_texture.image_data.width), &(loaded_texture.image_data.height), &(loaded_texture.image_data.nb_channel), 0);
        return std::make_pair(name, loaded_texture);
    }

    std::pair<std::string, LoadedTextureCubemap> AssetsLoader::LoadTextureCubemap(const std::string& name, const std::array<std::string, 6>& filepaths, const bool& SRGB)
    {
        LoadedTextureCubemap loaded_texture;
        loaded_texture.filepaths = filepaths;
        loaded_texture.srgb = SRGB;

        stbi_set_flip_vertically_on_load(false);
        for(unsigned int i = 0; i < 6; i++)
        {
            loaded_texture.image_datas.at(i).data = stbi_load(filepaths.at(i).c_str(), &(loaded_texture.image_datas.at(i).width), &(loaded_texture.image_datas.at(i).height), &(loaded_texture.image_datas.at(i).nb_channel), 0);
            if(loaded_texture.image_datas.at(i).data == NULL)
            {
                throw std::runtime_error(std::string("Impossible de lire l'image : " + filepaths.at(i)));
            }
        }

        return std::make_pair(name, loaded_texture);
    }

    std::pair<std::string, LoadedShader> AssetsLoader::LoadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
    {
        // Variables pour lire les fichiers de vertex et de fragment
        std::string vShaderCode;
        std::string fShaderCode;

        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        // Gerer les exceptions lors de la lecture des fichiers
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        std::string vPath = vertexPath;
        std::string fPath = fragmentPath;

        // Ouverture des fichiers
        vShaderFile.open(vPath.c_str());
        fShaderFile.open(fPath.c_str());

        // On lit le contenu des fichiers qu'on stock dans les variables
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // Fichiers lus - Fermeture des fichiers
        vShaderFile.close();
        fShaderFile.close();

        // On convertit le tout en chaîne de caracteres
        vShaderCode = vShaderStream.str();
        fShaderCode = fShaderStream.str();

        return std::make_pair(name, LoadedShader(vShaderCode, fShaderCode, std::nullopt));
    }

    std::pair<std::string, LoadedModel> AssetsLoader::LoadModel(const std::string& name, const std::string& filepath, const bool flipUV)
    {
        LoadedModel loaded_model;
        Assimp::Importer importer;

        // Lire la "scène" du fichier 3D
        const aiScene* scene{ importer.ReadFile(filepath, aiProcessPreset_TargetRealtime_Fast) };

        loaded_model.directory = filepath.substr(0, filepath.find_last_of('/'));
        loaded_model.filename = filepath;

        // Gestion des erreurs
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            throw std::runtime_error(importer.GetErrorString());

        // Parcourir chaque noeud du modèle 3D pour le charger
        processNodeModel(scene->mRootNode, scene, loaded_model.directory, loaded_model, flipUV);

        // Libérer la scène une fois le modèle chargé
        importer.FreeScene();
        return std::pair(name, loaded_model);
    }

    void AssetsLoader::processNodeModel(aiNode* node, const aiScene* scene, const std::string& directory, LoadedModel& loaded_model, const bool& flipUV)
    {
        glm::dmat4 transform{ AiMatrix4x4ToGlm(&node->mTransformation) * glm::dmat4(1.f) };
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* assimpMesh{ scene->mMeshes[node->mMeshes[i]] };
            LoadedMesh loaded_mesh{ processMeshModel(assimpMesh, scene, directory, flipUV) };

            // Transmettre les transformations du noeud sur la maille
            loaded_mesh.transform = transform;
            
            // Ajouter la maille au vector de maille
            loaded_model.meshes.push_back(loaded_mesh);
        }
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNodeModel(node->mChildren[i], scene, directory, loaded_model, flipUV);
        }
    }

    LoadedMesh AssetsLoader::processMeshModel(aiMesh* mesh, const aiScene* scene, const std::string& directory, const bool& flipUV)
    {
        std::vector<Vertex> vertices{};
        std::vector<unsigned int> indices{};
        std::vector<std::pair<std::string, LoadedTextureFile>> textures{};
        std::vector<std::pair<std::string, LoadedTextureFile>> textures_loaded{};
        VertexBufferLayout vbl{};
        float opacity{0.f};

        // On créer d'abord le VBL avec les paramètres associés
        if(mesh->HasPositions())
            vbl.Push(3, "positions");
        if(mesh->HasNormals())
            vbl.Push(3, "normals");
        if(mesh->HasTextureCoords(0))
            vbl.Push(2, "texCoords");
        if(mesh->HasTangentsAndBitangents())
        {
            vbl.Push(3, "tangent");
            vbl.Push(3, "bitangent");
        }

        // On parcourt l'ensemble des données de notre mesh
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector; // Pour convertir les vec3 de Assimp en glm::vec3

            if (mesh->HasPositions())
            {
                vector.x = mesh->mVertices[i].x;
                vector.y = mesh->mVertices[i].y;
                vector.z = mesh->mVertices[i].z;
                vertex.Position = vector;
            }
            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.Normal = vector;
            }
            if (mesh->HasTextureCoords(0)) // Si la mesh contient des TexCoords
            {
                glm::vec2 vec;
                // Une texture peut avoir jusqu'a 8 TexCoords differents, ici on considere seulement qu'il n'en existe qu'une (0)
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            }
            else
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);

            if (mesh->HasTangentsAndBitangents())
            {
                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vertex.Tangent = vector;

                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vertex.Bitangent = vector;
            }

            // On ajoute le Vertex avec les infos remplies
            vertices.push_back(vertex);
        }

        // Récuperer les indices de la maille
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face{ mesh->mFaces[i] };
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        // Récupérer l'opacité de la maille
        aiMaterial* mesh_material{ scene->mMaterials[mesh->mMaterialIndex] };
        mesh_material->Get(AI_MATKEY_OPACITY, opacity);

        // Récupérer les textures associées
        processTextureMeshModel(mesh_material, aiTextureType_DIFFUSE, flipUV, directory, textures, textures_loaded);
        processTextureMeshModel(mesh_material, aiTextureType_SPECULAR, flipUV, directory, textures, textures_loaded);
        processTextureMeshModel(mesh_material, aiTextureType_TRANSMISSION, flipUV, directory, textures, textures_loaded);
        processTextureMeshModel(mesh_material, aiTextureType_AMBIENT, flipUV, directory, textures, textures_loaded);
        processTextureMeshModel(mesh_material, aiTextureType_EMISSIVE, flipUV, directory, textures, textures_loaded);
        processTextureMeshModel(mesh_material, aiTextureType_HEIGHT, flipUV, directory, textures, textures_loaded);
        processTextureMeshModel(mesh_material, aiTextureType_NORMALS, flipUV, directory, textures, textures_loaded);

        // On défini le scale de la mesh à 1, car ça dépend du noeud (et pas de la maille en elle même)
        return LoadedMesh(vertices, indices, textures, vbl, opacity, glm::dmat4(1.f));
    }

    void AssetsLoader::processTextureMeshModel(aiMaterial* mat, aiTextureType type, const bool& flipUV, const std::string& directory, std::vector<std::pair<std::string, LoadedTextureFile>>& textures, std::vector<std::pair<std::string, LoadedTextureFile>>& textures_loaded)
    {
        bool srgb{ true };
        TextureType texType;
        switch (type)
        {
            case aiTextureType_DIFFUSE:
                texType = TextureType::Texture_DIFFUSE;
            break;
            case aiTextureType_SPECULAR:
                texType = TextureType::Texture_SPECULAR;
            break;
            case aiTextureType_TRANSMISSION:
                texType = TextureType::Texture_SPECULAR;
            break;
            case aiTextureType_AMBIENT:
                texType = TextureType::Texture_AMBIENT;
            break;
            case aiTextureType_EMISSIVE:
                texType = TextureType::Texture_EMISSIVE;
            break;
            case aiTextureType_HEIGHT:
                texType = TextureType::Texture_HEIGHT;
                srgb = false;
            break;
            case aiTextureType_NORMALS:
                texType = TextureType::Texture_NORMAL;
                srgb = false;
            break;
            default:
                throw std::runtime_error("Impossible de trouver le type de texture");
            break;
        }

        // Parcourir l'ensemble des textures du types choisis - Voir pour charger l'ensemble des textures des types que l'on a besoin
        for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString filepath;
            mat->GetTexture(type, i, &filepath);
            bool skip{ false };

            // Si la texture est déjà chargé, on évite de la chargée une deuxième fois
            for(auto& texture : textures_loaded)
            {
                auto filename{ texture.second.filepath.substr(0, texture.second.filepath.find_last_of('/')) };
                if(std::strcmp(filename.c_str(), filepath.C_Str()) == 0)
                {
                    textures.push_back(texture);
                    skip = true;
                    break;
                }
            }

            // Sinon, on charge la texture
            if(!skip)
            {
                std::string name{ std::string(filepath.C_Str()) };
                auto pair_texture{ LoadTextureFile(name, std::string(directory + "/" + filepath.C_Str()), texType, flipUV, srgb) };
                textures.push_back(pair_texture);
                textures_loaded.push_back(pair_texture);
            }
        }
    }

    //https://stackoverflow.com/questions/73611341/assimp-gltf-meshes-not-properly-scaled
    glm::dmat4 AssetsLoader::AiMatrix4x4ToGlm(const aiMatrix4x4* from)
    {
        glm::dmat4 to;

        to[0][0] = (GLfloat)from->a1; to[0][1] = (GLfloat)from->b1;  to[0][2] = (GLfloat)from->c1; to[0][3] = (GLfloat)from->d1;
        to[1][0] = (GLfloat)from->a2; to[1][1] = (GLfloat)from->b2;  to[1][2] = (GLfloat)from->c2; to[1][3] = (GLfloat)from->d2;
        to[2][0] = (GLfloat)from->a3; to[2][1] = (GLfloat)from->b3;  to[2][2] = (GLfloat)from->c3; to[2][3] = (GLfloat)from->d3;
        to[3][0] = (GLfloat)from->a4; to[3][1] = (GLfloat)from->b4;  to[3][2] = (GLfloat)from->c4; to[3][3] = (GLfloat)from->d4;

        return to;
    }
}