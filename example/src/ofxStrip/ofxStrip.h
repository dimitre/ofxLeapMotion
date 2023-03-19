//Written by Theo Watson - http://theowatson.com
//Work in progress class for doing opengl strips / ribbons

#pragma once
#include "ofMesh.h"
#include <glm/gtx/perpendicular.hpp>

using std::vector;

class ofxStrip{

	public:

		ofxStrip(){
			bTexCoords = true;
			bNormals = true;
			tex_u = 1.0;
			tex_v = 1.0;
		}

		void clear(){
			mesh.clear();
		}

		void setTexCoordScale( float tex_u_scale, float tex_v_scale ){
			tex_u = tex_u_scale;
			tex_v = tex_v_scale;
		}

		void generate( vector <glm::vec3> pts, float fixedWidth, glm::vec3 upVec){
			vector <float> width;
			width.push_back(fixedWidth);
			generate( pts, width, upVec);
		}

		void generate( vector <glm::vec3> pts, vector <float> width, glm::vec3 upVec){
			bool  bFixedWidth = false;
			float curWidth;
			float maxWidth = 0;


			if( width.size() == 1 || ( width.size() && width.size() != pts.size() ) ){
				bFixedWidth = true;
				curWidth  = width[0];
				maxWidth  = curWidth;
			}

			if( !bFixedWidth ){
				for(int i = 0; i < width.size(); i++){
					if( maxWidth > width[i] ){
						maxWidth = width[i];
					}
				}
			}

			mesh.clear();
			mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

			float numPts = pts.size()-1;
			for(int i = 1; i < pts.size(); i++){

				if( !bFixedWidth ){
					curWidth = width[i];
				}

				//find this point and the next point
				glm::vec3 & thisPoint = pts[i-1];
				glm::vec3 & nextPoint = pts[i];

				glm::vec3 delta		= nextPoint - thisPoint;
				glm::vec3 deltaNorm	= glm::normalize(delta); //.normalized();

//				ofVec3f toTheLeft	= deltaNorm.getPerpendicular(upVec);
				auto toTheLeft	= glm::gtx::perpendicular::perp(upVec); //deltaNorm.getPerpendicular(upVec);

				glm::vec3 L = thisPoint + toTheLeft * curWidth;
				glm::vec3 R = thisPoint - toTheLeft * curWidth;

				mesh.addVertex(L);
				mesh.addVertex(R);

				if( bNormals ){
					glm::vec3 normal = glm::gtx::perp(-toTheLeft);
					//deltaNorm.getPerpendicular(-toTheLeft);
					mesh.addNormal(normal);
					mesh.addNormal(normal);
				}

				if( bTexCoords ){
					float texUPct = curWidth / maxWidth;
					float texVPct = (float)(i-1) / numPts;

					mesh.addTexCoord(glm::vec2((1.0-texUPct) * tex_u, texVPct * tex_v));
					mesh.addTexCoord(glm::vec2(texUPct * tex_u, texVPct * tex_v));
				}
			}

			mesh.setupIndicesAuto();

		}

		void enableTexCoords(){
			bTexCoords = true;
		}

		void disableTexCoords(){
			bTexCoords = false;
		}

		void enableNormals(){
			bNormals = true;
		}

		void disableNormals(){
			bNormals = false;
		}

		ofMesh getMesh(){
			return mesh;
		}

		float tex_u, tex_v;
		bool bTexCoords;
		bool bNormals;

		ofMesh mesh;
};
