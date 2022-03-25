#include <iostream>
#include <climits>
#include "object/mesh/MeshUtil.h"
#include "object/native/Triangle.h"
#include "material/Lambertian.h"
#include "material/Metal.h"
#include "object/mesh/MeshTriangle.h"
#include "material/Dielectric.h"

bool MeshUtil::loadPureModelFromObj(const std::string & filename, std::vector<Hittable *> * objs, Material * mat) {
    FILE * fp = fopen(filename.c_str(), "r");
    if (!fp) {
        // error open file
        return false;
    }

    // store all vertices
    std::vector<Vector3d> vertices;

    // store all normals
    std::vector<Vector3d> normals;

    // store vertices corresponding to some polygon face
    std::vector<MeshPoint> mps;

    int c = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (c == 'v') {
            c = fgetc(fp);
            if (c == 'n') {
                // normal vector
                float x = 0, y = 0, z = 0;
                fscanf(fp, "%f %f %f", &x, &y, &z);
                normals.emplace_back(x, y, z);
            } else if (c == ' ') {
                // a vertex
                float x = 0, y = 0, z = 0;
                fscanf(fp, "%f %f %f", &x, &y, &z);
                vertices.emplace_back(x, y, z);
            }
        } else if (c == 'f') {
            c = fgetc(fp);
            if (c == ' ') {
                // a polygon
                mps.clear();
                int vi = -1, vni = -1;
                while (true) {
                    vi = vni = 0;
                    // leading space
                    while ((c = fgetc(fp)) == ' ');
                    // index of the v
                    vi = c - '0';
                    while ((c = fgetc(fp)) != '/') {
                        vi = vi * 10 + c - '0';
                    }
                    // index of the vt
                    while ((c = fgetc(fp)) != '/');
                    // index of the vn
                    c = fgetc(fp);
                    while (c != ' ' && c != '\n') {
                        vni = vni * 10 + c - '0';
                        c = fgetc(fp);
                    }
                    if (vi == 0 || vni == 0) {
                        break;
                    }
                    if (vi > 0 && vni > 0) {
                        mps.push_back({vertices[vi - 1], normals[vni - 1]});
                    } else if (vi < 0 && vni < 0) {
                        mps.push_back({vertices[vertices.size() + vi], normals[normals.size() + vni]});
                    }
                    // line end
                    if (c == '\n') {
                        break;
                    }
                }
                if (mps.size() < 3) {
                    // broken polygon
                    return false;
                }
                for (int i = 1; i < mps.size() - 1; ++i) {
                    objs->push_back(new MeshTriangle(mps[0], mps[i], mps[i + 1], mat));
                }
            }
        }
        // omit rest of the line
        if (c != '\n') {
            c = fgetc(fp);
            while (c != '\n' && c != EOF) {
                c = fgetc(fp);
            }
        }
    }

    fclose(fp);

    return true;
}
