#ifndef SHADER_H
#define SHADER_H

namespace Geometry {

class Shader {
private:
	// use a specific shader
	void useShader(const char* fileName, int type) const;
public:
	unsigned int id;

	Shader();
	Shader(const char* vertexName, const char* fragmentName);
	~Shader();

	// use the program
	void use();
	void link() const;
	// set uniforms. note: need to call use() before setting  ** (almost sure)
	void setBool (const char* name, bool      value) const;
	void setInt  (const char* name, int       value) const;
	void setFloat(const char* name, float     value) const;
	void setMat2 (const char* name, float* mat2x2  ) const;
	void setMat3 (const char* name, float* mat3x3  ) const;
	void setMat4 (const char* name, float* mat4x4  ) const;
	void setVec2 (const char* name, float* vec3    ) const;
	void setVec3 (const char* name, float* vec3    ) const;
};

}; // namespace Geometry

#endif