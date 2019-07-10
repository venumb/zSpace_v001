#pragma once

#include <headers/framework/data/zDatabase.h>

#include <headers/api/functionsets/zFnMeshField.h>
#include <headers/api/functionsets/zFnMesh.h>
#include <headers/api/functionsets/zFnGraph.h>


namespace zSpace
{

	/** \addtogroup API
	*	\brief The Application Program Interface of the library.
	*  @{
	*/

	/** \addtogroup zToolsets
	*	\brief Collection of toolsets for applications.
	*  @{
	*/

	/** \addtogroup zTsData
	*	\brief toolsets for data related utilities.
	*  @{
	*/

	/** \addtogroup zOSM
	*	\brief The data classes and structs for open street map toolset.
	*  @{
	*/

	/*! \struct zWays
	*	\brief A struct for storing  information of OSM ways and street graph.
	*	\since version 0.0.2
	*/

	/** @}*/

	/** @}*/

	/** @}*/

	/** @}*/

	struct zWays
	{
		/*! \brief stores index of the way in a ways container.		*/
		int id;

		/*! \brief stores index of the OSM way.		*/
		string OS_wayId;

		/*! \brief container of streetgraph edges which correspond to the OSM way ID.		*/
		vector<int> streetGraph_edgeId;

		/*! \brief stores type of the building as given by OSM.		*/
		zDataStreet streetType;

	};

	/** \addtogroup API
	*	\brief The Application Program Interface of the library.
	*  @{
	*/

	/** \addtogroup zToolsets
	*	\brief Collection of toolsets for applications.
	*  @{
	*/

	/** \addtogroup zTsData
	*	\brief toolsets for data related utilities.
	*  @{
	*/

	/** \addtogroup zOSM
	*	\brief The data classes and structs for open street map toolset.
	*  @{
	*/

	/*! \struct zBuildings
	*	\brief A class for accessing the openstreet data and other city level data stored in a SQL database , CSV files etc.
	*	\details Uses open source data from https://www.openstreetmap.org
	*	\since version 0.0.2
	*/

	/** @}*/

	/** @}*/

	/** @}*/

	/** @}*/

	struct zBuildings
	{
		/*! \brief stores index of the way in a buildings container.		*/
		int id;

		/*! \brief stores index of the OSM way.		*/
		string OS_wayId;

		/*! \brief container of building graph edges which correspond to the OSM way ID.		*/
		vector<int> buildingGraph_edgeId;

		/*! \brief stores type of the building as given by OSM.		*/
		zDataBuilding buildingType;

		double height;

		string postcode;
		

	};


	struct zPostcode
	{
		string postcode;

		vector<double> residentialPrices;

		zVector point;
	};

	/** \addtogroup API
	*	\brief The Application Program Interface of the library.
	*  @{
	*/

	/** \addtogroup zToolsets
	*	\brief Collection of toolsets for applications.
	*  @{
	*/

	/** \addtogroup zTsData
	*	\brief toolsets for data related utilities.
	*  @{
	*/

	/** \addtogroup zOSM
	*	\brief The data classes and structs for open street map toolset.
	*  @{
	*/

	/*! \class zTsOSM
	*	\brief A class for open street map data visualization.
	*	\since version 0.0.2
	*/

	/** @}*/

	/** @}*/

	/** @}*/

	/** @}*/
	class zTsOSM
	{
	protected:
		//--------------------------
		//---- PROTECTED ATTRIBUTES
		//--------------------------

		/*!	\brief core utilities Object  */
		zUtilsCore coreUtils;

		/*!	\brief pointer to a 2D field  */
		zObjMeshField<double> *fieldObj;

		//--------------------------
		//---- STREET ATTRIBUTES
		//--------------------------

		/*!	\brief pointer to a street graph object  */
		zObjGraph *streetObj;

		/*! \brief stores current number of ways		*/
		int n_zWays;

		/*! \brief zWays container		*/
		zWays *way;

		/*!	\brief street graph edgeId to wayId map. Used to get correponding wayId given the street graph EdgeId.  */
		map <int, string> streetEdges_Way;

		/*!	\brief OSMwayId to wayId. Used to get correponding street graph edges given the osm way id.  */
		unordered_map <string, int> OSMwaysID_zWayId;

		//--------------------------
		//---- BUILDING ATTRIBUTES
		//--------------------------

		/*!	\brief pointer to a building graph object  */
		
		zObjGraph *buildingGraphObj;

		zObjMesh *buildingObj;

		/*! \brief stores current number of buildings		*/
		int n_zBuildings;

		/*! \brief zBuildings container		*/
		zBuildings *buildings;

		/*!	\brief building graph edgeId to wayId map. Used to get correponding wayId given the building graph EdgeId.  */
		map <int, string> buildingEdges_Building;

		/*!	\brief OSMwayId to zbuildingId. Used to get correponding building graph edges given the osm way id.  */
		unordered_map <string, int> OSMwaysID_zBuildingsId;

		//--------------------------
		//---- POSTCODE ATTRIBUTES
		//--------------------------
		unordered_map <string, int> postcode_zPostcodeId;

		//--------------------------
		//---- BOUNDS ATTRIBUTES
		//--------------------------
		
		/*!	\brief minimum bounds of OSM data in 3D space given by a zVector.  */
		zVector minBB;

		/*!	\brief maximum bounds of OSM data in 3D space given by a zVector.  */
		zVector maxBB;

		//--------------------------
		//---- DATABASE ATTRIBUTES
		//--------------------------

		/*!	\brief database needed to acces the OSM and other data.  */
		zDatabase *zDB;

	public:
		//--------------------------
		//---- PUBLIC ATTRIBUTES
		//--------------------------

		/*!	\brief bounds of OSM data in latitute and logitude.  */
		double lat_lon[4];

		double scaleFactor;

		/*!	\brief field function set  */
		zFnMeshField<double> fnField;

		/*!	\brief graph function set for streets */
		zFnGraph fnStreet;

		/*!	\brief graph function set for buildings */
		zFnGraph fnGraphBuilding;
		zFnMesh fnBuilding;

		/*!	\brief 2 dimensional container of stream positions per field index.  */
		vector<vector<zVector>> fieldIndex_streamPositions;

		vector<zVector> buildingCenters;

		vector<zPostcode> postcodes;

		vector<zVector> tubeStations;

		vector<zVector> parks;

		//--------------------------
		//---- CONSTRUCTOR
		//--------------------------

		/*! \brief Default constructor.
		*
		*	\since version 0.0.2
		*/
		zTsOSM()
		{
			zDB = nullptr;

			fieldObj = nullptr;

			streetObj = nullptr;

			buildingObj = nullptr;

			buildingGraphObj = nullptr;
		}

		/*! \brief Overloaded constructor.
		*
		*	\param		[in]	DatabaseFileName		- file path to the SQL database.
		*	\since version 0.0.1
		*/
		zTsOSM(char* DatabaseFileName, zObjMeshField<double> &_fieldObj, zObjGraph &_streetObj, zObjMesh &_buildingObj, zObjGraph &_buildingGraphObj)
		{
			zDB = new zDatabase(DatabaseFileName);
			
			fieldObj = &_fieldObj;
			fnField = zFnMeshField<double>(_fieldObj);

			streetObj = &_streetObj;
			fnStreet = zFnGraph(_streetObj);

			buildingObj = &_buildingObj;
			fnBuilding = zFnMesh(_buildingObj);

			buildingGraphObj = &_buildingGraphObj;
			fnGraphBuilding = zFnGraph(_buildingGraphObj);

		}

		//--------------------------
		//---- DESTRUCTOR
		//--------------------------

		/*! \brief Default destructor.
		*
		*	\since version 0.0.2
		*/
		~zTsOSM() {}

		//--------------------------
		//---- COMPUTE METHODS
		//--------------------------

		/*! \brief This method sets the scale factor.
		*
		*	\param		[in]	scaleFactor		- scale of the map to be displayed.
		*	\since version 0.0.1
		*/
		void setScale(double _scaleFactor)
		{
			scaleFactor = _scaleFactor;
		}

		/*! \brief This method computes the bounding box in 3D space of the OSM data from the  lat_lon container of the bounds.
		*
		*	\since version 0.0.1
		*/
		void computeBoundingBox()
		{
			double diagonalDist = computeDistance(this->lat_lon[0], this->lat_lon[1], this->lat_lon[2], this->lat_lon[3]) * scaleFactor;

			double distLat = computeDistance(this->lat_lon[0], this->lat_lon[1], this->lat_lon[2], this->lat_lon[1]) * scaleFactor;

			double distLon = computeDistance(this->lat_lon[0], this->lat_lon[1], this->lat_lon[0], this->lat_lon[3]) * scaleFactor;

			minBB = zVector(-distLon * 0.5, -distLat * 0.5, 0);
			maxBB = zVector(distLon * 0.5, distLat * 0.5, 0);

			printf("\n diagonal distance: %1.2f ", diagonalDist);
		}

		/*! \brief This method computes the distance between two geo-points given by input latitute and longitude.
		*
		*	\details based on https://www.movable-type.co.uk/scripts/latlong.html using Haversine formula.
		*	\param		[in]	lat1		- latitude of geo-point 1.
		*	\param		[in]	lon1		- longitude of geo-point 1.
		*	\param		[in]	lat2		- latitude of geo-point 2.
		*	\param		[in]	lon2		- longitude of geo-point 2.
		*	\return				double		- distance between points in kilometers.
		*	\since version 0.0.1
		*/
		double computeDistance(double &lat1, double &lon1, double &lat2, double &lon2)
		{
			double R = 6378.137; // Radius of earth in KM

			double dLat = (lat2 * PI / 180) - (lat1 * PI / 180);
			double dLon = (lon2 * PI / 180) - (lon1 * PI / 180);

			double a = sin(dLat / 2) * sin(dLat / 2) + cos(lat1 * PI / 180) * cos(lat2 * PI / 180) * sin(dLon / 2) * sin(dLon / 2);
			double c = 2 * atan2(sqrt(a), sqrt(1 - a));
			double d = R * c;

			return d; // in kilometers
		}

		/*! \brief This method computes the 3D position based on the input latitude and longitude, using the bounds of the OSM data as the domain.
		*
		*	\param		[in]	lat		- input latitude.
		*	\param		[in]	lon		- input longitude.
		*	\return				zVector	- output vector.
		*	\since version 0.0.1
		*/
		zVector computePositionFromCoordinates(double &lat, double &lon)
		{
			double mappedX = coreUtils.ofMap(lon, lat_lon[1], lat_lon[3], minBB.x, maxBB.x);
			double mappedY = coreUtils.ofMap(lat, lat_lon[0], lat_lon[2], minBB.y, maxBB.y);

			//printf("\n X : %1.2f Y: %1.2f", mappedX, mappedY);

			return zVector(mappedX, mappedY, 0);
		}

		//--------------------------
		//---- CREATE METHODS
		//--------------------------

		/*! \brief This method create the scalar field from the bounds and input resolution.
		*
		*	\param		[in]	_n_X		- number of pixels in x direction.
		*	\param		[in]	_n_Y		- number of pixels in y direction.
		*/
		void createFieldFromBounds(int _n_X = 100, int _n_Y = 100)
		{
			zVector offset(0.5, 0.5, 0);

			fnField.create(minBB - offset, maxBB + offset, _n_X, _n_Y);
		}

		/*! \brief This method creates the streets from the OSM data.
		*
		*	\param		[in]	edgeCol		- input color to be assigned to the edges of the graph.
		*	\since version 0.0.1
		*/
		void createStreets(zColor streetCol = zColor(0, 0, 0, 1))
		{
			vector<zVector>(positions);
			vector<int>(edgeConnects);

			unordered_map <string, int> node_streetVertices;
			map <int, string> streetVertices_Node;


			vector<string> outStm_nodes;
			vector<string> sqlStm_nodes = { " SELECT * FROM nodes WHERE id IN (SELECT node_id FROM ways_nodes WHERE way_id IN (SELECT id FROM ways_tags WHERE ways_tags.k = \"highway\")) ;" };
			bool stat = zDB->sqlCommand(sqlStm_nodes, zSelect, false, outStm_nodes, false);


			printf("\n outStm_nodes: %i", outStm_nodes.size());

			for (int i = 0; i < outStm_nodes.size(); i += 3)
			{


				string hashKey = outStm_nodes[i];;
				node_streetVertices[hashKey] = positions.size();

				streetVertices_Node[positions.size()] = hashKey;

				double lat = atof(outStm_nodes[i + 1].c_str());
				double lon = atof(outStm_nodes[i + 2].c_str());

				zVector pos = computePositionFromCoordinates(lat, lon);

				positions.push_back(pos);


			}

			vector<string> outStm_ways;
			vector<string> sqlStm_ways = { " SELECT * FROM ways_nodes WHERE way_id IN (SELECT id FROM ways_tags WHERE ways_tags.k = \"highway\");" };
			stat = zDB->sqlCommand(sqlStm_ways, zSelect, false, outStm_ways, false);

			printf("\n outStm_ways: %i", outStm_ways.size());

			way = new zWays[outStm_ways.size()];
			n_zWays = 0;

			for (int i = 0; i < outStm_ways.size() - 3; i += 3)
			{
				if (i != 0) i -= 3;

				string wayId = outStm_ways[i];

				way[n_zWays].id = n_zWays;
				way[n_zWays].OS_wayId = wayId;

				way[n_zWays].streetType = getStreetType(wayId);

				// map
				OSMwaysID_zWayId[wayId] = n_zWays;

				while (outStm_ways[i] == wayId && i < outStm_ways.size() - 3)
				{
					string hashKey = outStm_ways[i + 1];
					std::unordered_map<string, int>::const_iterator got = node_streetVertices.find(hashKey);

					if (got != node_streetVertices.end())
					{
						if (outStm_ways[i + 3] == wayId)
						{
							string hashKey1 = outStm_ways[i + 3 + 1].c_str();
							std::unordered_map<string, int>::const_iterator got1 = node_streetVertices.find(hashKey1);

							if (got1 != node_streetVertices.end())
							{
								way[n_zWays].streetGraph_edgeId.push_back(edgeConnects.size());
								streetEdges_Way[edgeConnects.size()] = wayId;
								edgeConnects.push_back(got->second);

								way[n_zWays].streetGraph_edgeId.push_back(edgeConnects.size());
								streetEdges_Way[edgeConnects.size()] = wayId;
								edgeConnects.push_back(got1->second);

							}

						}
					}

					i += 3;
				}

				n_zWays++;
			}
					   
			fnStreet.create(positions, edgeConnects);	
			fnStreet.setEdgeColor(streetCol, false);	

		}

		/*! \brief This method creates the building graph from the OSM data.
		*
		*	\param		[in]	edgeCol		- input color to be assigned to the edges of the graph.
		*	\since version 0.0.1
		*/

		void createGraphBuildings(zColor buildingCol = zColor(0, 0, 0, 1))
		{
			vector<zVector>(positions);
			vector<int>(edgeConnects);

			unordered_map <string, int> node_buildingVertices;
			map <int, string> buildingVertices_Node;


			vector<string> outStm_nodes;
			vector<string> sqlStm_nodes = { " SELECT * FROM nodes WHERE id IN (SELECT node_id FROM ways_nodes WHERE way_id IN (SELECT id FROM ways_tags WHERE ways_tags.k = \"building\")) ;" };
			bool stat = zDB->sqlCommand(sqlStm_nodes, zSelect, false, outStm_nodes, false);

			printf("\n outStm_nodes: %i", outStm_nodes.size());

			for (int i = 0; i < outStm_nodes.size(); i += 3)
			{


				string hashKey = outStm_nodes[i];;
				node_buildingVertices[hashKey] = positions.size();

				buildingVertices_Node[positions.size()] = hashKey;

				double lat = atof(outStm_nodes[i + 1].c_str());
				double lon = atof(outStm_nodes[i + 2].c_str());

				zVector pos = computePositionFromCoordinates(lat, lon);

				positions.push_back(pos);


			}

			vector<string> outStm_ways;
			vector<string> sqlStm_ways = { " SELECT * FROM ways_nodes WHERE way_id IN (SELECT id FROM ways_tags WHERE ways_tags.k = \"building\");" };
			stat = zDB->sqlCommand(sqlStm_ways, zSelect, false, outStm_ways, false);

			printf("\n outStm_ways: %i", outStm_ways.size());

			buildings = new zBuildings[outStm_ways.size()];
			n_zBuildings = 0;

			for (int i = 0; i < outStm_ways.size() - 3; i += 3)
			{
				if (i != 0) i -= 3;

				string wayId = outStm_ways[i];

				buildings[n_zBuildings].id = n_zBuildings;
				buildings[n_zBuildings].OS_wayId = wayId;

				buildings[n_zBuildings].buildingType = getBuildingType(wayId);

				// map
				OSMwaysID_zBuildingsId[wayId] = n_zBuildings;

				while (outStm_ways[i] == wayId && i < outStm_ways.size() - 3)
				{
					string hashKey = outStm_ways[i + 1];
					std::unordered_map<string, int>::const_iterator got = node_buildingVertices.find(hashKey);

					if (got != node_buildingVertices.end())
					{
						if (outStm_ways[i + 3] == wayId)
						{


							string hashKey1 = outStm_ways[i + 3 + 1].c_str();
							std::unordered_map<string, int>::const_iterator got1 = node_buildingVertices.find(hashKey1);


							if (got1 != node_buildingVertices.end())
							{
								buildings[n_zBuildings].buildingGraph_edgeId.push_back(edgeConnects.size());
								buildingEdges_Building[edgeConnects.size()] = wayId;
								edgeConnects.push_back(got->second);

								buildings[n_zBuildings].buildingGraph_edgeId.push_back(edgeConnects.size());
								buildingEdges_Building[edgeConnects.size()] = wayId;
								edgeConnects.push_back(got1->second);

							}

						}
					}

					i += 3;
				}

				n_zBuildings++;
			}

			printf(" \n num Buildings %i ", n_zBuildings);

			fnGraphBuilding.create(positions, edgeConnects);
			fnGraphBuilding.setEdgeColor(buildingCol, false);

			// compute centers
			for (int i = 0; i < n_zBuildings; i++)
			{
				zVector cen(0,0,0);
				
				for (int j = 0; j < buildings[i].buildingGraph_edgeId.size(); j++)
				{
					zItGraphHalfEdge he(*buildingGraphObj, buildings[i].buildingGraph_edgeId[j]);

					zVector p = he.getVertex().getVertexPosition();

					cen += p;

					if (i == 100) printf(" \n %i ", buildings[i].buildingGraph_edgeId[j]);
				}

				cen /= buildings[i].buildingGraph_edgeId.size();

				//printf("\n %i, %1.2f %1.2f %1.2f ", i, cen.x, cen.y, cen.z);

				buildingCenters.push_back(cen);

			}				
			

		}

		void exportGraphBuildings(string outfile)
		{
			ofstream myfile;

			//string outfile = "C:/Users/vishu/Desktop/OSMData/buildings.txt";
			myfile.open(outfile.c_str());

			if (myfile.fail())
			{
				cout << " error in opening file  " << outfile.c_str() << endl;
				return;

			}

			for (auto &vPos : buildingGraphObj->graph.vertexPositions)
			{				
				myfile << "\n v " << vPos.x << " " << vPos.y << " " << vPos.z;
			}


			for (int i = 0; i < n_zBuildings; i++)
			{
				myfile << "\n #";

				for (int j = 0; j < buildings[i].buildingGraph_edgeId.size(); j++)
				{
					zItGraphHalfEdge he(*buildingGraphObj, buildings[i].buildingGraph_edgeId[j]);

					int v2 = he.getVertex().getId();
					int v1 = he.getStartVertex().getId();

					myfile << "\n e ";

					myfile << v1 << " ";
					myfile << v2;
				}

				
				if(i == n_zBuildings -1) myfile << "\n #";

			}

			myfile.close();
			cout << endl << " TXT exported. File:   " << outfile.c_str() << endl;
		}

		void exportPartGraphBuildings(string outfile)
		{
			ofstream myfile;

			//string outfile = "C:/Users/vishu/Desktop/OSMData/buildings.txt";
			myfile.open(outfile.c_str());

			if (myfile.fail())
			{
				cout << " error in opening file  " << outfile.c_str() << endl;
				return;

			}
					

			vector<zVector> positions;
			unordered_map<int, int> vertexMap;
			int numB = 10;


			for (int i = 0; i < numB; i++)
			{
				myfile << "\n #";

				for (int j = 0; j < buildings[i].buildingGraph_edgeId.size(); j++)
				{
					zItGraphHalfEdge he(*buildingGraphObj, buildings[i].buildingGraph_edgeId[j]);


					int v1 = he.getStartVertex().getId();
					std::unordered_map<int, int>::const_iterator got1 = vertexMap.find(v1);
					if (got1 != vertexMap.end()) v1 = got1->second;
					else
					{
						vertexMap[v1] = positions.size();
						v1 = positions.size();
						positions.push_back(he.getStartVertex().getVertexPosition());

					}

					int v2 = he.getVertex().getId();
					std::unordered_map<int, int>::const_iterator got2 = vertexMap.find(v2);
					if (got2 != vertexMap.end()) v2 = got2->second;
					else 
					{
						vertexMap[v2] = positions.size();						
						v2 = positions.size();
						positions.push_back(he.getVertex().getVertexPosition());

					}

					

					myfile << "\n e ";

					myfile << v1 << " ";
					myfile << v2;
				}


				if (i == numB - 1) myfile << "\n #";

			}

			for (auto &vPos : positions)
			{
				myfile << "\n v " << vPos.x << " " << vPos.y << " " << vPos.z;
			}

			myfile.close();
			cout << endl << " TXT exported. File:   " << outfile.c_str() << endl;
		}

		void createBuildings(zColor buildingCol = zColor(0, 0, 0, 1))
		{
			vector<zVector>(positions);
			vector<int>(polyConnects);
			vector<int>(polyCounts);


			unordered_map <string, int> node_buildingVertices;
			map <int, string> buildingVertices_Node;


			vector<string> outStm_nodes;
			vector<string> sqlStm_nodes = { " SELECT * FROM building_nodes WHERE shapeId IN (SELECT DISTINCT shapeId FROM building_nodes WHERE lat >=" + to_string(lat_lon[0]) 
				+ " AND lat <= " + to_string(lat_lon[2]) + " AND lon >=" + to_string(lat_lon[1])+ " AND lon <=" + to_string(lat_lon[3]) + ")  ORDER BY rowid;" };
			bool stat = zDB->sqlCommand(sqlStm_nodes, zSelect, false, outStm_nodes, false);

			printf("\n outStm_nodes: %i", outStm_nodes.size());

			buildings = new zBuildings[outStm_nodes.size()];
			n_zBuildings = 0;

			

			for (int i = 0; i < outStm_nodes.size()-3; i += 3)
			{
				string hashKey = outStm_nodes[i];;
				int pCounts = 0;

				

				vector<int> tempConnects;

				while (outStm_nodes[i] == hashKey)
				{
					tempConnects.push_back(positions.size());

					double lat = atof(outStm_nodes[i + 1].c_str());
					double lon = atof(outStm_nodes[i + 2].c_str());

					zVector pos = computePositionFromCoordinates(lat, lon);

					positions.push_back(pos);
					pCounts++;

					i += 3;
				}

				vector<string> parts = coreUtils.splitString(hashKey, ".");


				if (pCounts >= 3 && parts.size() == 1)
				{
					polyCounts.push_back(pCounts);

					for (auto id : tempConnects) polyConnects.push_back(id);

					buildings[n_zBuildings].id = n_zBuildings;
					buildings[n_zBuildings].OS_wayId = hashKey;

					// map
					OSMwaysID_zBuildingsId[hashKey] = n_zBuildings;

					n_zBuildings++;
				}				

				i -= 3;
			}	
					


			fnBuilding.create(positions,polyCounts, polyConnects);
			fnBuilding.setFaceColor(buildingCol, false);

			zVector *pos = fnBuilding.getRawVertexPositions();

			// get Building Heights
			vector<string> outStm_heights;
			vector<string> sqlStm_heights = { " SELECT shapeId, buildingHeight FROM building_outlines WHERE shapeId IN (SELECT DISTINCT shapeId FROM building_nodes WHERE lat >=" + to_string(lat_lon[0])
				+ " AND lat <= " + to_string(lat_lon[2]) + " AND lon >=" + to_string(lat_lon[1]) + " AND lon <=" + to_string(lat_lon[3]) + ")  ORDER BY rowid;" };
			stat = zDB->sqlCommand(sqlStm_heights, zSelect, false, outStm_heights, false);

			printf("\n outStm_heights: %i", outStm_heights.size());



			for (int i = 0; i < outStm_heights.size(); i += 2)
			{
				string shapeId = outStm_heights[i];

				std::unordered_map<string, int>::const_iterator got = OSMwaysID_zBuildingsId.find(shapeId);

				if (got != node_buildingVertices.end())
				{
					buildings[got->second].height = atof(outStm_heights[i+1].c_str());

					//printf("\n %i %1.2f ", got->second, atof(outStm_heights[i + 1].c_str()));

					zItMeshFace f(*buildingObj, got->second);

					vector<int> fVerts;
					f.getVertices(fVerts);

					for (auto vID : fVerts) pos[vID].z = buildings[got->second].height *0.001 * scaleFactor;
				}

			}


			



		}


		void getPostcodesPrices()
		{
			// get postcodes

			vector<string> outStm_postcodes;
			
			vector<string> sqlStm_postcodes = { "SELECT data_residentialprices.postcode, data_residentialprices.price, postcodes_latlon_london.lat, postcodes_latlon_london.lon FROM data_residentialprices INNER JOIN postcodes_latlon_london ON postcodes_latlon_london.postCode = data_residentialprices.postcode WHERE postcodes_latlon_london.lat >= " + to_string(lat_lon[0]) 
				+ " AND postcodes_latlon_london.lat <= " + to_string(lat_lon[2]) + " AND postcodes_latlon_london.lon >=" + to_string(lat_lon[1]) + " AND postcodes_latlon_london.lon <=" + to_string(lat_lon[3]) + ";" };



			//vector<string> sqlStm_postcodes = { "SELECT data_residentialprices.postcode, data_residentialprices.price, postcodes_latlon_london.lat, postcodes_latlon_london.lon FROM data_residentialprices INNER JOIN postcodes_latlon_london ON postcodes_latlon_london.postCode = data_residentialprices.postcode WHERE postcodes_latlon_london.lat >= " + to_string(lat_lon[0])
			//+ " AND postcodes_latlon_london.lat <= " + to_string(lat_lon[2]) + " AND postcodes_latlon_london.lon >=" + to_string(lat_lon[1]) + " AND postcodes_latlon_london.lon <=" + to_string(lat_lon[3]) + "  ORDER BY rowid;" };

			
			bool stat = zDB->sqlCommand(sqlStm_postcodes, zSelect, false, outStm_postcodes, false);
			


		
			printf("\n outStm_postcodes: %i", outStm_postcodes.size());

			for (int i = 0; i < outStm_postcodes.size(); i += 4)
			{
				string hashKey = outStm_postcodes[i];;
				int pCounts = 0;

				double lat = atof(outStm_postcodes[i + 2].c_str());
				double lon = atof(outStm_postcodes[i + 3].c_str());

				zVector pos = computePositionFromCoordinates(lat, lon);

				zPostcode temp;

				temp.postcode = hashKey;
				temp.point = pos;

				

				while (outStm_postcodes[i] == hashKey)
				{
					temp.residentialPrices.push_back(atof(outStm_postcodes[i + 1].c_str()));

					if (postcodes.size() == 0) printf("\n %s ", outStm_postcodes[i + 1].c_str());

					i += 4;
				}

				postcodes.push_back(temp);

				// map
				postcode_zPostcodeId[hashKey] = postcodes.size() - 1;		

				i -= 4;

			}

		}

		void getTubeStations()
		{
			vector<string> outStm_tubenodes;
			
			vector<string> sqlStm_tubenodes = { "SELECT * FROM stations_tube_london WHERE lat >= " + to_string(lat_lon[0])
						+ " AND lat <= " + to_string(lat_lon[2]) + " AND lon >=" + to_string(lat_lon[1]) + " AND lon <=" + to_string(lat_lon[3]) + ";" };


			//vector<string> sqlStm_tubenodes = { "SELECT * FROM stations_tube_london;" };

			bool stat = zDB->sqlCommand(sqlStm_tubenodes, zSelect, false, outStm_tubenodes, false);

			printf("\n outStm_tubenodes: %i", outStm_tubenodes.size());

			tubeStations.clear();

			for (int i = 0; i < outStm_tubenodes.size(); i += 5)
			{				

				double lat = atof(outStm_tubenodes[i + 1].c_str());
				double lon = atof(outStm_tubenodes[i + 2].c_str());

				zVector pos = computePositionFromCoordinates(lat, lon);

				tubeStations.push_back(pos);
			}


		}

		void exportTubeStations(string outfile)
		{

			ofstream myfile;

			myfile.open(outfile.c_str());

			if (myfile.fail())
			{
				cout << " error in opening file  " << outfile.c_str() << endl;
				return;

			}

			for (auto &vPos : tubeStations)
			{
				myfile << "\n v " << vPos.x << " " << vPos.y << " " << vPos.z;
			}

			myfile.close();
			cout << endl << " TXT exported. File:   " << outfile.c_str() << endl;
		}

		void getParks()
		{
			vector<string> outStm_parknodes;

			vector<string> sqlStm_parknodes = { "SELECT * FROM nodes WHERE id IN (SELECT node_id FROM ways_nodes WHERE way_id IN (SELECT id FROM ways_tags WHERE ways_tags.k = \"leisure\" AND ways_tags.v = \"park\")) ;" };


			//vector<string> sqlStm_tubenodes = { "SELECT * FROM stations_tube_london;" };

			bool stat = zDB->sqlCommand(sqlStm_parknodes, zSelect, false, outStm_parknodes, false);

			printf("\n outStm_parknodes: %i", outStm_parknodes.size());

			parks.clear();

			for (int i = 0; i < outStm_parknodes.size(); i += 3)
			{

				double lat = atof(outStm_parknodes[i + 1].c_str());
				double lon = atof(outStm_parknodes[i + 2].c_str());

				zVector pos = computePositionFromCoordinates(lat, lon);

				parks.push_back(pos);
			}


		}

		void exportParks(string outfile)
		{

			ofstream myfile;

			myfile.open(outfile.c_str());

			if (myfile.fail())
			{
				cout << " error in opening file  " << outfile.c_str() << endl;
				return;

			}

			for (auto &vPos : parks)
			{
				myfile << "\n v " << vPos.x << " " << vPos.y << " " << vPos.z;
			}

			myfile.close();
			cout << endl << " TXT exported. File:   " << outfile.c_str() << endl;
		}

		//--------------------------
		//---- GET METHODS
		//--------------------------

		/*! \brief This method gets the street type from the OSM data for the given wayId if it corresponds to a street.
		*
		*	\param		[in]	wayId		- input wayId.
		*	\since version 0.0.1
		*/
		zDataStreet getStreetType(string wayId)
		{
			vector<string> outStm;
			vector<string> sqlStm = { "SELECT v FROM ways_tags WHERE ways_tags.id = " + wayId + ";" };
			bool stat = zDB->sqlCommand(sqlStm, zSelect, false, outStm, false);



			zDataStreet out = zUndefinedStreet;

			if (outStm.size() > 0)
			{
				if (outStm[0] == "trunk" || outStm[0] == "trunk_link") out = zTrunkStreet;

				if (outStm[0] == "primary" || outStm[0] == "primary_link") out = zPrimaryStreet;

				if (outStm[0] == "secondary" || outStm[0] == "secondary_link") out = zSecondaryStreet;

				if (outStm[0] == "tertiary" || outStm[0] == "tertiary_link") out = zTertiaryStreet;

				if (outStm[0] == "residential" || outStm[0] == "living_street") out = zResidentialStreet;

				if (outStm[0] == "pedestrian" || outStm[0] == "footway") out = zPrimaryStreet;

				if (outStm[0] == "cycleway") out = zCycleStreet;

				if (outStm[0] == "service") out = zServiceStreet;

			}


			return out;

		}

		/*! \brief This method extracts the edges from the street graph based on the input key and value for OSM ways tags.
		*
		*	\param		[in]	k			- key of the relations tag.
		*	\param		[in]	v			- value of the relations tag.
		*	\param		[out]	graphEdges	- edge indicies correponding to k and v.
		*	\since version 0.0.1
		*/
		void getStreetEdgesFromWays(string k, string v, vector<int> &graphEdges)
		{
			graphEdges.clear();

			vector<string> outStm_wayIds;
			vector<string> sqlStm_wayIds = { " SELECT id FROM ways_tags WHERE ways_tags.k = \"" + k + "\" AND way_tags.v =\"" + v + "\";" };
			bool stat = zDB->sqlCommand(sqlStm_wayIds, zSelect, false, outStm_wayIds, false);

			for (int i = 0; i < outStm_wayIds.size(); i += 1)
			{


				string hashKey = outStm_wayIds[i];;
				int zWayId;

				bool chk = coreUtils.existsInMap(hashKey, OSMwaysID_zWayId, zWayId);

				if (chk)
				{
					for (int j = 0; j < way[zWayId].streetGraph_edgeId.size(); j++)
					{
						graphEdges.push_back(way[zWayId].streetGraph_edgeId[j]);
					}
				}
			}

		}

		/*! \brief This method extracts the edges from the street graph based on the input key and value for OSM relations tags.
		*
		*	\param		[in]	k			- key of the relations tag.
		*	\param		[in]	v			- value of the relations tag.
		*	\param		[out]	graphEdges	- edge indicies correponding to k and v.
		*	\since version 0.0.1
		*/
		void getStreetEdgesFromRelations(string k, string v, vector<int> &graphEdges)
		{
			graphEdges.clear();

			vector<string> outStm_wayIds;
			vector<string> sqlStm_wayIds = { " SELECT ref FROM relations_members WHERE id  IN ( SELECT id FROM relations_tags WHERE relations_tags.k = \"" + k + "\" AND relations_tags.v =\"" + v + "\");" };
			bool stat = zDB->sqlCommand(sqlStm_wayIds, zSelect, false, outStm_wayIds, false);

			for (int i = 0; i < outStm_wayIds.size(); i += 1)
			{


				string hashKey = outStm_wayIds[i];;
				int zWayId;

				bool chk = coreUtils.existsInMap(hashKey, OSMwaysID_zWayId, zWayId);

				if (chk)
				{
					for (int j = 0; j < way[zWayId].streetGraph_edgeId.size(); j++)
					{
						graphEdges.push_back(way[zWayId].streetGraph_edgeId[j]);
					}
				}
			}

		}

		/*! \brief This method gets the street type from the OSM data for the given wayId if it corresponds to a street.
		*
		*	\param		[in]	wayId		- input wayId.
		*	\since version 0.0.1
		*/
		zDataBuilding getBuildingType(string wayId)
		{
			vector<string> outStm;
			vector<string> sqlStm = { "SELECT v FROM ways_tags WHERE ways_tags.id = " + wayId + ";" };
			bool stat = zDB->sqlCommand(sqlStm, zSelect, false, outStm, false);



			zDataBuilding out = zUndefinedBuilding;

			if (outStm.size() > 0)
			{
				if (outStm[0] == "office" || outStm[0] == "commercial" || outStm[0] == "hotel" || outStm[0] == "theatre" || outStm[0] == "retail") out = zCommercialBuilding;
				if (outStm[0] == "Commercial" || outStm[0] == "Arts_&_Office_Complex" || outStm[0] == "shop" || outStm[0] == "offices") out = zCommercialBuilding;

				if (outStm[0] == "apartments" || outStm[0] == "flats" || outStm[0] == "residential" || outStm[0] == "council_flats") out = zResidentialBuilding;
				if (outStm[0] == "house" || outStm[0] == "hall_of_residence" || outStm[0] == "Student hostel") out = zResidentialBuilding;

				if (outStm[0] == "gallery" || outStm[0] == "hospital" || outStm[0] == "church" || outStm[0] == "place_of_worship" || outStm[0] == "museum" || outStm[0] == "cathedral") out = zPublicBuilding;
				if (outStm[0] == "railway_station" || outStm[0] == "Community_Building" || outStm[0] == "train_station" || outStm[0] == "station" || outStm[0] == "civic") out = zPublicBuilding;

				if (outStm[0] == "school" || outStm[0] == "university" || outStm[0] == "college" || outStm[0] == "Nursery,_School") out = zUniversityBuilding;

			}


			return out;

		}

		//--------------------------
		//---- DATA FACTORY METHODS
		//--------------------------

		/*! \brief This method gets graph and data attributes from input shape CSV data files.
		*
		*	\param		[in]	infile_Nodes		- input file name including the directory path and extension for position information.
		*	\param		[in]	infile_Attribute	- input file name including the directory path and extension for attribute information.
		*	\param		[in]	attributeData		- container for sttribute data as a string.
		*	\since version 0.0.1
		*/
		zObjGraph fromShapeCSV(string infile_Nodes, string infile_Attribute, vector<vector<string>> &attributeData)
		{

			zObjGraph out;

			attributeData.clear();

			vector<zVector> positions;
			vector<int> edgeConnects;

			unordered_map <string, int> positionVertex;

			vector<string> shapeIds;

			// nodes
			ifstream myfile;
			myfile.open(infile_Nodes.c_str());

			if (myfile.fail())
			{
				cout << " \n error in opening file  " << infile_Nodes.c_str() << endl;
				return out;

			}

			while (!myfile.eof())
			{
				string str;
				getline(myfile, str);

				vector<string> perlineData = coreUtils.splitString(str, ",");

			
				for (int i = 0; i < perlineData.size(); i++)
				{

					if (perlineData[0] == " " || perlineData[0] == "\"shapeid\"") continue;

					string shapeId = (perlineData[0]);					

					vector<int> tempConnects;

					//printf("\n%s : ", shapeId.c_str());
					bool exit = false;									
				
					
					do
					{
						if (perlineData[0] == " ")continue;
						
			

						vector<string> x = coreUtils.splitString(perlineData[2], "\"");
						vector<string> y = coreUtils.splitString(perlineData[1], "\"");

						//printf("\n %s %s |", x[0].c_str(), y[0].c_str());

						double lat = atof(x[0].c_str());
						double lon = atof(y[0].c_str());

						// get mapped position

						zVector p0 = computePositionFromCoordinates(lat, lon);

						// check if position alread exists. 
						int v0;
						bool vExists = coreUtils.vertexExists(positionVertex, p0,3, v0);

						if (!vExists)
						{
							v0 = positions.size();
							positions.push_back(p0);

							string hashKey = (to_string(p0.x) + "," + to_string(p0.y) + "," + to_string(p0.z));
							positionVertex[hashKey] = v0;
						}

					
						tempConnects.push_back(v0);



						if (!myfile.eof())
						{
							getline(myfile, str);
							perlineData.clear();
							perlineData = coreUtils.splitString(str, ",");
						}
						else exit = true;

						if (myfile.eof()) exit = true;
						else
						{					
							if (perlineData[0] != shapeId) 	exit = true;
						}
							
						
							
					} while (!exit);
													
					if (tempConnects.size() > 1)
					{
						for (int k = 0; k < tempConnects.size() - 1; k++)
						{
							edgeConnects.push_back(tempConnects[k]);
							edgeConnects.push_back(tempConnects[k + 1]);


						}
					}
								
									
					
				}
			}

			myfile.close();

			printf("\n positions: %i ", positions.size());
			
			
			
			out.graph.create(positions, edgeConnects);


			// attributes

	

			myfile.open(infile_Attribute.c_str());

			if (myfile.fail())
			{
				cout << " \n error in opening file  " << infile_Attribute.c_str() << endl;
				return out;

			}

			while (!myfile.eof())
			{
				string str;
				getline(myfile, str);

				vector<string> perlineData = coreUtils.splitString(str, ",");

				if (perlineData.size() < 1) continue;

				if (perlineData[0] == " ") continue;

				if (perlineData[0] == "\"shapeid\"") continue;
				

				vector<string> data;

				for (int i = 0; i < perlineData.size(); i++)
				{
					
					vector<string> attrib = coreUtils.splitString(perlineData[i], "\"");
					data.push_back(attrib[0]);

				}

				if( data.size() > 0) attributeData.push_back(data);

			}

			myfile.close();
				
			return out;
		}

		/*! \brief This method gets mesh and data attributes from input shape CSV data files.
		*
		*	\param		[in]	infile_Nodes		- input file name including the directory path and extension for position information.
		*	\param		[in]	infile_Attribute	- input file name including the directory path and extension for attribute information.
		*	\param		[in]	attributeData		- container for sttribute data as a string.
		*	\since version 0.0.1
		*/
		zObjMesh fromCoordinates_ShapeCSV(string infile_Nodes, string infile_Attribute, vector<vector<string>> &attributeData)
		{

			zObjMesh out;

			attributeData.clear();

			vector<zVector> positions;
			vector<int> polyConnects;
			vector<int> polyCounts;

			unordered_map <string, int> positionVertex;

			vector<string> shapeIds;

			// nodes
			ifstream myfile;
			myfile.open(infile_Nodes.c_str());

			if (myfile.fail())
			{
				cout << " \n error in opening file  " << infile_Nodes.c_str() << endl;
				return out;

			}

			while (!myfile.eof())
			{
				string str;
				getline(myfile, str);

				vector<string> perlineData = coreUtils.splitString(str, ",");


				for (int i = 0; i < perlineData.size(); i++)
				{

					if (perlineData[0] == " " || perlineData[0] == "\"shapeid\"") continue;

					string shapeId = (perlineData[0]);

					vector<int> tempConnects;

					//printf("\n%s : ", shapeId.c_str());
					bool exit = false;


					do
					{
						if (perlineData[0] == " ")continue;



						vector<string> x = coreUtils.splitString(perlineData[2], "\"");
						vector<string> y = coreUtils.splitString(perlineData[1], "\"");

						//printf("\n %s %s |", x[0].c_str(), y[0].c_str());

						double lat = atof(x[0].c_str());
						double lon = atof(y[0].c_str());

						// get mapped position

						zVector p0 = computePositionFromCoordinates(lat, lon);

						// check if position alread exists. 
						int v0;
						bool vExists = coreUtils.vertexExists(positionVertex, p0,3, v0);

						if (!vExists)
						{
							v0 = positions.size();
							positions.push_back(p0);

							string hashKey = (to_string(p0.x) + "," + to_string(p0.y) + "," + to_string(p0.z));
							positionVertex[hashKey] = v0;
						}


						if (!vExists) tempConnects.push_back(v0);



						if (!myfile.eof())
						{
							getline(myfile, str);
							perlineData.clear();
							perlineData = coreUtils.splitString(str, ",");
						}
						else exit = true;

						if (myfile.eof()) exit = true;
						else
						{
							if (perlineData[0] != shapeId) 	exit = true;
						}



					} while (!exit);


					if (tempConnects.size() >= 3)
					{
						for (int k = 0; k < tempConnects.size(); k++)
						{
							polyConnects.push_back(tempConnects[k]);
						}

						polyCounts.push_back(tempConnects.size());
					}



				}
			}

			myfile.close();

			//printf("\n positions: %i , polyCounts: %i, polyConnects: %i  ", positions.size(), polyCounts.size(), polyConnects.size());
			
			
			out.mesh.create(positions, polyCounts, polyConnects);

			

			// attributes



			myfile.open(infile_Attribute.c_str());

			if (myfile.fail())
			{
				cout << " \n error in opening file  " << infile_Attribute.c_str() << endl;
				return out;

			}

			while (!myfile.eof())
			{
				string str;
				getline(myfile, str);

				vector<string> perlineData = coreUtils.splitString(str, ",");

				if (perlineData.size() < 1) continue;

				if (perlineData[0] == " ") continue;

				if (perlineData[0] == "\"shapeid\"") continue;


				vector<string> data;

				for (int i = 0; i < perlineData.size(); i++)
				{

					vector<string> attrib = coreUtils.splitString(perlineData[i], "\"");
					data.push_back(attrib[0]);

				}

				if (data.size() > 0) attributeData.push_back(data);

			}

			myfile.close();


			return out;

		}


		//--------------------------
		//---- FIELD DATA METHODS
		//--------------------------

		/*! \brief This method updates the scalars in the scalar field based on input graph connectivity.
		*
		*	\param		[in]	inGraph		- input graph.
		*	\since version 0.0.1
		*/
		void updateScalars_GraphConnectivity(zObjGraph& inGraph)
		{
			for (int i = 0; i < fnField.numFieldValues(); i++)
			{
				fnField.setFieldValue(0.0, i);
			}

			for(zItGraphVertex v(inGraph); !v.end(); v.next())		
			{
				int fieldIndex;
				zVector pos = v.getVertexPosition();
				bool boundsCheck = fnField.getIndex(pos, fieldIndex);

				if (boundsCheck) continue;

				int valence = v.getVertexValence();

				fnField.setFieldValue((double)valence, fieldIndex);

			}
		}

		/*! \brief This method updates the scalars in the scalar field based on input CSV data file with format - lat,lon,data.
		*
		*	\tparam				T			- Type to work with standard c++ datatypes of int, float,double, string.
		*	\param		[in]	infilename	- input file name including the directory path and extension.
		*	\param		[out]	data		- output data.
		*	\since version 0.0.1
		*/
		template <typename T>
		void updateScalars_fromCSV(string infilename, vector<T> &data);

		/*! \brief This method updates the scalars in the scalar field and gets data positions based on input CSV data file with format - lat,lon,data.
		*
		*	\tparam				T				- Type to work with standard c++ datatypes of int, float,double, string.
		*	\param		[in]	infilename		- input file name including the directory path and extension.
		*	\param		[out]	dataPositions	- output positions in the bounds of the map.
		*	\param		[out]	data			- output data.
		*	\since version 0.0.1
		*/
		template <typename T>
		void updateScalars_fromCSV(string infilename, vector<zVector> &dataPositions, vector<T> &data);


		/*! \brief This method exports the relations from an OSM file to 3 CSV files.
		*
		*	\param		[in]	infilename						- input file name including the directory path and extension.
		*	\param		[out]	outfilename_Relations			- output CSV file of relation ids.
		*	\param		[out]	outfilename_Relations_members	- output CSV file of relation members.
		*	\param		[out]	outfilename_RelationTags		- output CSV file of relation tags.
		*	\since version 0.0.1
		*/
		void exportOSMRelationsToCSV(string infilename, string outfilename_Relations, string outfilename_Relations_members, string outfilename_RelationTags)
		{
			vector<string> relations;
			vector<vector<string>> relations_members;
			vector<vector<string>> relationsTags;

			// nodes
			ifstream myfile;
			myfile.open(infilename.c_str());

			if (myfile.fail())
			{
				cout << " \n error in opening file  " << infilename.c_str() << endl;
				return;

			}
			bool exit = false;
			while (!myfile.eof() && !exit)
			{
				string str;
				getline(myfile, str);

				vector<string> perlineData = coreUtils.splitString(str, " ");

				if (perlineData.size() == 0) continue;

				if (perlineData[0] == "</osm>") exit = true;

				if (perlineData[0] == "<relation")
				{
					vector<string> relationId = coreUtils.splitString(perlineData[1], "\"");

					printf("\n %s ", perlineData[1].c_str());

					relations.push_back(relationId[1]);

					while (perlineData[0] != "</relation>")
					{
						perlineData.clear();
						str.clear();
						getline(myfile, str);
						perlineData = coreUtils.splitString(str, " ");

						if (perlineData[0] == "<member")
						{
							vector<string> type = coreUtils.splitString(perlineData[1], "\"");
							vector<string> ref = coreUtils.splitString(perlineData[2], "\"");


							vector<string> temp;

							temp.push_back(relationId[1]);
							temp.push_back(type[1]);
							temp.push_back(ref[1]);

							relations_members.push_back(temp);
						}

						if (perlineData[0] == "<tag")
						{
							vector<string> k = coreUtils.splitString(perlineData[1], "\"");
							vector<string> v = coreUtils.splitString(perlineData[2], "\"");


							vector<string> temp;

							temp.push_back(relationId[1]);
							temp.push_back(k[1]);
							temp.push_back(v[1]);

							relationsTags.push_back(temp);

						}
					}
				}
			}

			myfile.close();


			// exportToCSV _ Relations

			ofstream myExportfile;
			myExportfile.open(outfilename_Relations.c_str());

			if (myfile.fail())
			{
				cout << " error in opening file  " << outfilename_Relations.c_str() << endl;
				return;

			}

			myExportfile << "id";


			for (int i = 0; i < relations.size(); i++)
			{
				myExportfile << "\n" << relations[i];
			}

			myExportfile.close();


			// exportToCSV _ Relations_members

			myExportfile.open(outfilename_Relations_members.c_str());

			if (myfile.fail())
			{
				cout << " error in opening file  " << outfilename_Relations_members.c_str() << endl;
				return;

			}

			myExportfile << "id,type,ref";


			for (int i = 0; i < relations_members.size(); i++)
			{
				myExportfile << "\n";
				for (int j = 0; j < relations_members[i].size(); j++)
				{
					myExportfile << relations_members[i][j];

					if (j != relations_members[i].size() - 1) myExportfile << ",";
				}
			}

			myExportfile.close();



			// exportToCSV_relationsTags


			myExportfile.open(outfilename_RelationTags.c_str());

			if (myfile.fail())
			{
				cout << " error in opening file  " << outfilename_RelationTags.c_str() << endl;
				return;

			}

			myExportfile << "id,k,v";


			for (int i = 0; i < relationsTags.size(); i++)
			{
				myExportfile << "\n";
				for (int j = 0; j < relationsTags[i].size(); j++)
				{
					myExportfile << relationsTags[i][j];

					if (j != relationsTags[i].size() - 1) myExportfile << ",";
				}
			}

			myExportfile.close();

		}


	};

#ifndef DOXYGEN_SHOULD_SKIP_THIS

	//--------------------------
	//---- TEMPLATE SPECIALIZATION DEFINITIONS 
	//--------------------------

	//---------------//

	//---- string specialization for updateScalars_fromCSV 
	template<>
	inline void zTsOSM::updateScalars_fromCSV(string infilename, vector<string>& data)
	{
		data.clear();

		for (int i = 0; i < fnField.numFieldValues(); i++)
		{
			fnField.setFieldValue(0.0, i);
		}

		ifstream myfile;
		myfile.open(infilename.c_str());

		if (myfile.fail())
		{
			cout << " error in opening file  " << infilename.c_str() << endl;
			return;

		}

		while (!myfile.eof())
		{
			string str;
			getline(myfile, str);

			vector<string> perlineData = coreUtils.splitString(str, ",");

			if (perlineData.size() != 3) continue;
			if (perlineData[0] == " ") continue;

			double lat = atof(perlineData[0].c_str());
			double lon = atof(perlineData[1].c_str());

			if (lat >= lat_lon[0] && lat <= lat_lon[2] && lon >= lat_lon[1] && lon <= lat_lon[3])
			{
				// get mapped position
				zVector pos = computePositionFromCoordinates(lat, lon);

				// get field index
				int fieldIndex;
				bool boundsCheck = fnField.getIndex(pos, fieldIndex);

				if (boundsCheck) continue;

				// get data
				string inData = (perlineData[2]);

				data.push_back(inData);

				double weight;
				fnField.getFieldValue(fieldIndex, weight);
				weight++;

				fnField.setFieldValue(weight, fieldIndex);

			}

		}

		myfile.close();
	}
	
	//---- double specialization for updateScalars_fromCSV 
	template <>
	inline void zTsOSM::updateScalars_fromCSV(string infilename, vector<double> &data)
	{
		data.clear();

		for (int i = 0; i < fnField.numFieldValues(); i++)
		{
			fnField.setFieldValue(0.0, i);
		}

		ifstream myfile;
		myfile.open(infilename.c_str());

		if (myfile.fail())
		{
			cout << " error in opening file  " << infilename.c_str() << endl;
			return;

		}

		while (!myfile.eof())
		{
			string str;
			getline(myfile, str);

			vector<string> perlineData = coreUtils.splitString(str, ",");

			if (perlineData.size() != 3) continue;
			if (perlineData[0] == " ") continue;

			double lat = atof(perlineData[0].c_str());
			double lon = atof(perlineData[1].c_str());

			if (lat >= lat_lon[0] && lat <= lat_lon[2] && lon >= lat_lon[1] && lon <= lat_lon[3])
			{
				// get mapped position
				zVector pos = computePositionFromCoordinates(lat, lon);

				// get field index
				int fieldIndex;;

				bool boundsCheck = fnField.getIndex(pos, fieldIndex);

				if (boundsCheck) continue;

				// get data
				double inData = atof(perlineData[2].c_str());

				data.push_back(inData);

				double weight;
				weight = inData;;

				fnField.setFieldValue(weight, fieldIndex);

			}







		}

		myfile.close();
	}

	//---- float specialization for updateScalars_fromCSV 
	template <>
	inline void zTsOSM::updateScalars_fromCSV(string infilename, vector<float> &data)
	{
		data.clear();

		for (int i = 0; i < fnField.numFieldValues(); i++)
		{
			fnField.setFieldValue(0.0, i);
		}

		ifstream myfile;
		myfile.open(infilename.c_str());

		if (myfile.fail())
		{
			cout << " error in opening file  " << infilename.c_str() << endl;
			return;

		}

		while (!myfile.eof())
		{
			string str;
			getline(myfile, str);

			vector<string> perlineData = coreUtils.splitString(str, ",");

			if (perlineData.size() != 3) continue;
			if (perlineData[0] == " ") continue;

			double lat = atof(perlineData[0].c_str());
			double lon = atof(perlineData[1].c_str());

			if (lat >= lat_lon[0] && lat <= lat_lon[2] && lon >= lat_lon[1] && lon <= lat_lon[3])
			{
				// get mapped position
				zVector pos = computePositionFromCoordinates(lat, lon);

				// get field index
				int fieldIndex;
				bool boundsCheck = fnField.getIndex(pos, fieldIndex);

				if (boundsCheck) continue;

				// get data
				double inData = atof(perlineData[2].c_str());

				data.push_back(inData);

				double weight;
				weight = inData;;

				fnField.setFieldValue(weight, fieldIndex);

			}


		}

		myfile.close();
	}

	//---- int specialization for updateScalars_fromCSV 
	template <>
	inline void zTsOSM::updateScalars_fromCSV(string infilename, vector<int> &data)
	{
		data.clear();

		for (int i = 0; i < fnField.numFieldValues(); i++)
		{
			fnField.setFieldValue(0.0, i);
		}

		ifstream myfile;
		myfile.open(infilename.c_str());

		if (myfile.fail())
		{
			cout << " error in opening file  " << infilename.c_str() << endl;
			return;

		}

		while (!myfile.eof())
		{
			string str;
			getline(myfile, str);

			vector<string> perlineData = coreUtils.splitString(str, ",");

			if (perlineData.size() != 3) continue;
			if (perlineData[0] == " ") continue;

			double lat = atof(perlineData[0].c_str());
			double lon = atof(perlineData[1].c_str());

			if (lat >= lat_lon[0] && lat <= lat_lon[2] && lon >= lat_lon[1] && lon <= lat_lon[3])
			{
				// get mapped position
				zVector pos = computePositionFromCoordinates(lat, lon);

				// get field index
				int fieldIndex;
				bool boundsCheck = fnField.getIndex(pos, fieldIndex);

				if (boundsCheck) continue;

				// get data
				double inData = atoi(perlineData[2].c_str());

				data.push_back(inData);

				double weight;
				weight = inData;;

				fnField.setFieldValue(weight, fieldIndex);

			}

		}

		myfile.close();
	}

	//---------------//

	//---- string specialization for updateScalars_fromCSV  with datapositions
	template<>
	inline void zTsOSM::updateScalars_fromCSV(string infilename, vector<zVector>& dataPositions, vector<string>& data)
	{
		dataPositions.clear();
		data.clear();

		ifstream myfile;
		myfile.open(infilename.c_str());

		if (myfile.fail())
		{
			cout << " \n error in opening file  " << infilename.c_str() << endl;
			return;

		}

		while (!myfile.eof())
		{
			string str;
			getline(myfile, str);

			vector<string> perlineData = coreUtils.splitString(str, ",");

			if (perlineData.size() != 3) continue;
			if (perlineData[0] == " ") continue;

			double lat = atof(perlineData[0].c_str());
			double lon = atof(perlineData[1].c_str());



			if (lat >= lat_lon[0] && lat <= lat_lon[2] && lon >= lat_lon[1] && lon <= lat_lon[3])
			{

				// get mapped position
				zVector pos = computePositionFromCoordinates(lat, lon);
				dataPositions.push_back(pos);

				// get field index
				int fieldIndex;
				bool boundsCheck = fnField.getIndex(pos, fieldIndex);

				if (boundsCheck) continue;

				// get data
				string inData = (perlineData[2]);

				data.push_back(inData);

				double weight;
				fnField.getFieldValue(fieldIndex, weight);
				weight++;

				fnField.setFieldValue(weight, fieldIndex);



			}

		}

		myfile.close();
	}

	//---- double specialization for updateScalars_fromCSV  with datapositions
	template <>
	inline void zTsOSM::updateScalars_fromCSV(string infilename, vector<zVector> &dataPositions, vector<double> &data)
	{
		dataPositions.clear();
		data.clear();

		ifstream myfile;
		myfile.open(infilename.c_str());

		if (myfile.fail())
		{
			cout << " \n error in opening file  " << infilename.c_str() << endl;
			return;

		}

		while (!myfile.eof())
		{
			string str;
			getline(myfile, str);

			vector<string> perlineData = coreUtils.splitString(str, ",");

			if (perlineData.size() != 3) continue;
			if (perlineData[0] == " ") continue;

			double lat = atof(perlineData[0].c_str());
			double lon = atof(perlineData[1].c_str());

			if (lat >= lat_lon[0] && lat <= lat_lon[2] && lon >= lat_lon[1] && lon <= lat_lon[3])
			{

				// get mapped position
				zVector pos = computePositionFromCoordinates(lat, lon);
				dataPositions.push_back(pos);

				// get field index
				int fieldIndex;
				bool boundsCheck = fnField.getIndex(pos, fieldIndex);

				if (boundsCheck) continue;

				// get data
				double inData = atof(perlineData[2].c_str());

				data.push_back(inData);

				double weight;
				weight = inData;;

				fnField.setFieldValue(weight, fieldIndex);
			}






		}

		myfile.close();
	}

	//---- float specialization for updateScalars_fromCSV  with datapositions
	template <>
	inline void zTsOSM::updateScalars_fromCSV(string infilename, vector<zVector> &dataPositions, vector<float> &data)
	{
		dataPositions.clear();
		data.clear();

		ifstream myfile;
		myfile.open(infilename.c_str());

		if (myfile.fail())
		{
			cout << " \n error in opening file  " << infilename.c_str() << endl;
			return;

		}

		while (!myfile.eof())
		{
			string str;
			getline(myfile, str);

			vector<string> perlineData = coreUtils.splitString(str, ",");

			if (perlineData.size() != 3) continue;
			if (perlineData[0] == " ") continue;

			double lat = atof(perlineData[0].c_str());
			double lon = atof(perlineData[1].c_str());



			if (lat >= lat_lon[0] && lat <= lat_lon[2] && lon >= lat_lon[1] && lon <= lat_lon[3])
			{

				// get mapped position
				zVector pos = computePositionFromCoordinates(lat, lon);
				dataPositions.push_back(pos);

				// get field index
				int fieldIndex;
				bool boundsCheck = fnField.getIndex(pos, fieldIndex);

				if (boundsCheck) continue;

				// get data
				double inData = atof(perlineData[2].c_str());

				data.push_back(inData);

				double weight;
				weight = inData;;

				fnField.setFieldValue(weight, fieldIndex);


			}



		}

		myfile.close();
	}

	//---- int specialization for updateScalars_fromCSV  with datapositions
	template <>
	inline void zTsOSM::updateScalars_fromCSV(string infilename, vector<zVector> &dataPositions, vector<int> &data)
	{
		dataPositions.clear();
		data.clear();

		ifstream myfile;
		myfile.open(infilename.c_str());

		if (myfile.fail())
		{
			cout << " \n error in opening file  " << infilename.c_str() << endl;
			return;

		}

		while (!myfile.eof())
		{
			string str;
			getline(myfile, str);

			vector<string> perlineData = coreUtils.splitString(str, ",");

			if (perlineData.size() != 3) continue;
			if (perlineData[0] == " ") continue;


			double lat = atof(perlineData[0].c_str());
			double lon = atof(perlineData[1].c_str());

			if (lat >= lat_lon[0] && lat <= lat_lon[2] && lon >= lat_lon[1] && lon <= lat_lon[3])
			{

				// get mapped position
				zVector pos = computePositionFromCoordinates(lat, lon);
				dataPositions.push_back(pos);

				// get field index
				int fieldIndex;
				bool boundsCheck = fnField.getIndex(pos, fieldIndex);

				if (boundsCheck) continue;

				// get data
				double inData = atoi(perlineData[2].c_str());

				data.push_back(inData);

				double weight;
				weight = inData;;

				fnField.setFieldValue(weight, fieldIndex);



			}

		}

		myfile.close();
	}

	
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
}