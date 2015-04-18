#include "Loaders.hpp"

#include "src/omicron/resource/ResourceServer.hpp"
#include "src/omicron/resource/loader/GeoThread.hpp"

namespace omi {

namespace loader {

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

Geometry* geoFromWavefront(const std::string& filePath) {

    // the unsorted lists of geometry data
    t_VertexArray vertices;
    t_UVArray     uv;
    t_NormalArray normals;
    // the sorted lists of geometry data
    t_VertexArray sortedVertices;
    t_UVArray     sortedUV;
    t_NormalArray sortedNormals;

    // open the file using the resource server
    VirtualFile file;
    ResourceServer::get( filePath, file );

    // iterate over the file
    while ( file.hasNextLine() )
    {
        // get the current line
        std::string line;
        file.nextLine( line );

        // split the line
        std::vector<std::string> elements;
        util::str::split(line, ' ', elements);

        // go to the next line if this is empty
        if (elements.size() == 0) {

            continue;
        }

        // vertex coord
        if (!elements[0].compare("v")) {

            // check that the line has a enough elements
            if (elements.size() < 4 || elements.size() > 4) {

                //TODO: throw an exception
                std::cout <<
                    "WAVEFRONT LOADER: wrong number of vertex coords" <<
                    std::endl;
            }

            // TODO: check if valid floats

            // add to the list of all vertices
            vertices.push_back(glm::vec3(
                    static_cast<float>(atof(elements[1].c_str())),
                    static_cast<float>(atof(elements[2].c_str())),
                    static_cast<float>(atof(elements[3].c_str()))));
        }
        // UV coordinate
        else if (!elements[0].compare("vt")) {

            // check that the line has a enough elements
            if (elements.size() < 3 || elements.size() > 3) {

                //TODO: throw an exception
                std::cout <<
                    "WAVEFRONT LOADER: wrong number of uv coords" <<
                    std::endl;
            }

            // TODO: check if valid floats

            // add to the list of all UV coordinates
            uv.push_back(glm::vec2(
                    static_cast<float>(atof(elements[1].c_str())),
                    static_cast<float>(atof(elements[2].c_str()))));
        }
        // normal
        else if (!elements[0].compare("vn")) {

            // check that the line has a enough elements
            if (elements.size() < 4 || elements.size() > 4) {

                //TODO: throw an exception
                std::cout <<
                    "WAVEFRONT LOADER: wrong number of normal coords" <<
                    std::endl;
            }

            // TODO: check if valid floats

            // add to the list of all vertices
            normals.push_back(glm::vec3(
                    static_cast<float>(atof(elements[1].c_str())),
                    static_cast<float>(atof(elements[2].c_str())),
                    static_cast<float>(atof(elements[3].c_str()))));
        }
        // face
        else if (!elements[0].compare("f")) {

            // check that the line has a enough elements
            if (elements.size() < 4 || elements.size() > 4) {

                //TODO: throw an exception
                std::cout <<
                    "WAVEFRONT LOADER: wrong number of face coords" <<
                    std::endl;
            }

            // iterate over the coordinates
            for (unsigned i = 0; i < 3; ++i) {

                //split again
                line = elements[i + 1];
                std::vector<std::string> faceCoords;
                util::str::split(line, '/', faceCoords);

                // TODO: check indices are valid unsigned ints

                // vertices only
                if (faceCoords.size() == 1) {

                    sortedVertices.push_back(
                        vertices[atoi(faceCoords[0].c_str()) - 1]);
                }
                // vertices and normals
                else if (faceCoords.size() == 2) {

                    sortedVertices.push_back(
                        vertices[atoi(faceCoords[0].c_str()) - 1]);
                    sortedNormals.push_back(
                        normals [atoi(faceCoords[1].c_str()) - 1]);
                }
                // vertices, UV coordinates, and normals
                else if (faceCoords.size() == 3) {

                    //add to the sorted lists
                    sortedVertices.push_back(
                        vertices[atoi(faceCoords[0].c_str()) - 1]);
                    sortedUV.push_back(
                        uv      [atoi(faceCoords[1].c_str()) - 1]);
                    sortedNormals.push_back(
                        normals [atoi(faceCoords[2].c_str()) - 1]);
                }
                else {

                    // TODO: error that shit!
                }
            }
        }
    }

    return new Geometry( sortedVertices, sortedUV, sortedNormals );
}

void geoFromKeyFrameWavefront(
        const std::string& path,
        std::map<std::string, std::vector<Geometry*>>& geoMap,
        std::map<std::string, std::vector<unsigned>>&  frameMap,
        std::string& defaultAni )
{
    // remove the key file from to get the parent path
    std::string parentPath = "";
    int ultimateSlash = path.find_last_of( "/" );
    if (  ultimateSlash != std::string::npos )
    {
        parentPath = path.substr( 0, ultimateSlash + 1 );
    }

    // this is a list of all threads we're using to load
    std::vector< std::unique_ptr<boost::thread> > loadingThreads;

    // open the file using the resource server
    VirtualFile file;
    ResourceServer::get( path, file );

    bool inAnimationBlock = false;
    // iterate over the file
    while ( file.hasNextLine() )
    {
        // get the current line
        std::string line;
        file.nextLine( line );

        // get default animation
        if ( util::str::beginsWith( line, "default:" ) )
        {
            // remove the default prefix
            defaultAni = line.substr( 9, line.length() );
        }
        // check for animation block begin
        else if ( line.compare( "animations begin:" ) == 0 )
        {
            inAnimationBlock = true;
        }
        // check for animation block end
        else if ( line.compare( "animations end" ) == 0 )
        {
            inAnimationBlock = false;
        }
        // get animation
        else if ( inAnimationBlock )
        {
            // don't do anything if there is no line here
            if ( line.length() ==0 )
            {
                continue;
            }

            // split by spaces
            std::vector<std::string> elements;
            util::str::split( line, ' ', elements );

            // get the name of the animation
            std::string aniName = elements[0];

            // build file path to the geometry
            std::string geoPath = parentPath + aniName + "/";

            // iterate over elements
            std::vector<Geometry*> geoList;
            std::vector<unsigned> frameList;
            for ( unsigned i = 1; i < elements.size(); ++i )
            {
                // load geometry
                std::stringstream ss;
                ss << geoPath << i << ".obj";

                // create the Geometry object
                Geometry* geo = new Geometry();
                geoList.push_back( geo );
                // create a thread
                loadingThreads.push_back(
                    std::unique_ptr<boost::thread>(
                        new boost::thread(
                            geo_thread::concurrentLoadGeo,
                            ss.str(),
                            geo
                        )
                    )
                );

                // TODO : REMOVE ME??
                // geoList.push_back( geoFromWavefront( ss.str() ) );

                // store frame number
                frameList.push_back( atoi( elements[i].c_str() ) );
            }

            // add animation to maps
            geoMap.insert( std::make_pair( aniName, geoList ) );
            frameMap.insert( std::make_pair( aniName, frameList ) );

            // TODO: case where there are no transitions
        }
        // unknown line
        else if ( line.length() > 0 )
        {
            std::cout << "--------" << std::endl;
            std::cout << "error unknown line in key file:" << std::endl;
            std::cout << path << std::endl;
            std::cout << "--------" << std::endl;
            std::cout << line << std::endl;
            std::cout << "--------" << std::endl;
        }
    }

    // wait for all loading threads to finish
    for ( unsigned i = 0; i < loadingThreads.size(); ++i )
    {
        loadingThreads[i]->join();
    }
}

} // namespace loader

} // namespace omi
