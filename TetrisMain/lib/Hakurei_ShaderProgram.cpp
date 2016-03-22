#include "Hakurei_ShaderProgram.h"


Uint8* fileContents(const char* srcf,Uint32* length)
{
    FILE* f = NULL;
    Uint8 buffer[BUFF_SIZE];
    Uint8* ret = NULL;
    int N;

    if((f=fopen(srcf,"rb")) == NULL)
    {
        CERR << "Error occurred: File " << srcf << " not found." << ENDL;
        exit(-1);
    }

    *length = 0;
    while((N=fread(buffer,sizeof(Uint8),BUFF_SIZE,f)) > 0)
    {
        if((ret = (Uint8*)realloc(ret,*length + BUFF_SIZE)) == NULL)
        {
            fclose(f);
            CERR << "Error occurred: Cannot (re)allocate return buffer." << ENDL;
            exit(-1);
        }
        for(int i=0;i<N;i++)
        {
            ret[*length] = buffer[i];
            (*length)++;
        }
    }

    fclose(f);
    return ret;
}

Hakurei::ShaderProgram::ShaderProgram(String vShader, String fShader)
{
    NO_PERMISSION
    attributes.clear();
    uniforms.clear();

    //---- CPU side for shader program
    Uint32 vLength, fLength;
    Uint8* vSource = fileContents(vShader.c_str(), &vLength);
    Uint8* fSource = fileContents(fShader.c_str(), &fLength);

    //---- GPU side (Load and compile)
    vShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShaderID, 1, (const GLchar**)&vSource, (const GLint*)&vLength);
    glCompileShader(vShaderID);
    fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShaderID, 1, (const GLchar**)&fSource, (const GLint*)&fLength);
    glCompileShader(fShaderID);

    //---- GPU side (link)
    progID = glCreateProgram();
    glAttachShader(progID, vShaderID);
    glAttachShader(progID, fShaderID);
    glLinkProgram(progID);

    //---- Get attributes location
    getAttributes();

    return;
}

void Hakurei::ShaderProgram::getAttributes()
{
    for(String attr : {ATTRIB_POSITION, ATTRIB_NORMAL, ATTRIB_TANGENT, ATTRIB_UV, ATTRIB_COLOR})
        attributes[attr] = glGetAttribLocation(progID, attr.c_str());
}

bool Hakurei::ShaderProgram::hasUniform(const String uniName)
{
    return uniforms.find(uniName) != uniforms.end();
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const Uint32 val)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniform1ui(loc, val);
    }
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const Sint32 val)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniform1i(loc, val);
    }
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const float val)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniform1f(loc, val);
    }
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const double val)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniform1d(loc, val);
    }
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const Vec2f& val)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniform2fv(loc, 1, glm::value_ptr(val));
    }
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const Vec3f& val)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniform3fv(loc, 1, glm::value_ptr(val));
    }
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const Vec4f& val)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniform4fv(loc, 1, glm::value_ptr(val));
    }
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const glm::mat2& val, bool transpose)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniformMatrix2fv(loc, 1, transpose, glm::value_ptr(val));
    }
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const glm::mat3& val, bool transpose)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniformMatrix3fv(loc, 1, transpose, glm::value_ptr(val));
    }
}

void Hakurei::ShaderProgram::setUniform(const String uniName, const glm::mat4& val, bool transpose)
{
    if(!hasUniform(uniName))
    {
        uniforms[uniName] = glGetUniformLocation(progID, uniName.c_str());
        if(uniforms.at(uniName) == -1)
        {
            CERR << "Warning : There is no uniform called " << uniName << " in shader program." << ENDL;
            return;
        }
    }
    if(uniforms.at(uniName) != -1)
    {
        Sint32 loc = uniforms.at(uniName);
        glUniformMatrix4fv(loc, 1, transpose, glm::value_ptr(val));
    }
}

