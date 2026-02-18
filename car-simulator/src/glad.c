#include <glad/glad.h>
#include <stdlib.h>

// Define function pointers
PFNGLCLEARPROC glad_glClear = NULL;
PFNGLCLEARCOLORPROC glad_glClearColor = NULL;
PFNGLVIEWPORTPROC glad_glViewport = NULL;
PFNGLENABLEPROC glad_glEnable = NULL;
PFNGLDISABLEPROC glad_glDisable = NULL;
PFNGLDEPTHFUNCPROC glad_glDepthFunc = NULL;
PFNGLGENBUFFERSPROC glad_glGenBuffers = NULL;
PFNGLBINDBUFFERPROC glad_glBindBuffer = NULL;
PFNGLBUFFERDATAPROC glad_glBufferData = NULL;
PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays = NULL;
PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer = NULL;
PFNGLCREATESHADERPROC glad_glCreateShader = NULL;
PFNGLSHADERSOURCEPROC glad_glShaderSource = NULL;
PFNGLCOMPILESHADERPROC glad_glCompileShader = NULL;
PFNGLGETSHADERIVPROC glad_glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog = NULL;
PFNGLCREATEPROGRAMPROC glad_glCreateProgram = NULL;
PFNGLATTACHSHADERPROC glad_glAttachShader = NULL;
PFNGLLINKPROGRAMPROC glad_glLinkProgram = NULL;
PFNGLGETPROGRAMIVPROC glad_glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog = NULL;
PFNGLDELETESHADERPROC glad_glDeleteShader = NULL;
PFNGLUSEPROGRAMPROC glad_glUseProgram = NULL;
PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation = NULL;
PFNGLUNIFORM1IPROC glad_glUniform1i = NULL;
PFNGLUNIFORM1FPROC glad_glUniform1f = NULL;
PFNGLUNIFORM3FPROC glad_glUniform3f = NULL;
PFNGLUNIFORM3FVPROC glad_glUniform3fv = NULL;
PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv = NULL;
PFNGLDRAWARRAYSPROC glad_glDrawArrays = NULL;
PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays = NULL;
PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers = NULL;

static void* get_proc(void* (*load)(const char *name), const char* namez) {
    void* result = load(namez);
    return result;
}

int gladLoadGLLoader(void* (*load)(const char *name)) {
    glad_glClear = (PFNGLCLEARPROC)get_proc(load, "glClear");
    glad_glClearColor = (PFNGLCLEARCOLORPROC)get_proc(load, "glClearColor");
    glad_glViewport = (PFNGLVIEWPORTPROC)get_proc(load, "glViewport");
    glad_glEnable = (PFNGLENABLEPROC)get_proc(load, "glEnable");
    glad_glDisable = (PFNGLDISABLEPROC)get_proc(load, "glDisable");
    glad_glDepthFunc = (PFNGLDEPTHFUNCPROC)get_proc(load, "glDepthFunc");
    glad_glGenBuffers = (PFNGLGENBUFFERSPROC)get_proc(load, "glGenBuffers");
    glad_glBindBuffer = (PFNGLBINDBUFFERPROC)get_proc(load, "glBindBuffer");
    glad_glBufferData = (PFNGLBUFFERDATAPROC)get_proc(load, "glBufferData");
    glad_glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)get_proc(load, "glGenVertexArrays");
    glad_glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)get_proc(load, "glBindVertexArray");
    glad_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)get_proc(load, "glEnableVertexAttribArray");
    glad_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)get_proc(load, "glVertexAttribPointer");
    glad_glCreateShader = (PFNGLCREATESHADERPROC)get_proc(load, "glCreateShader");
    glad_glShaderSource = (PFNGLSHADERSOURCEPROC)get_proc(load, "glShaderSource");
    glad_glCompileShader = (PFNGLCOMPILESHADERPROC)get_proc(load, "glCompileShader");
    glad_glGetShaderiv = (PFNGLGETSHADERIVPROC)get_proc(load, "glGetShaderiv");
    glad_glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)get_proc(load, "glGetShaderInfoLog");
    glad_glCreateProgram = (PFNGLCREATEPROGRAMPROC)get_proc(load, "glCreateProgram");
    glad_glAttachShader = (PFNGLATTACHSHADERPROC)get_proc(load, "glAttachShader");
    glad_glLinkProgram = (PFNGLLINKPROGRAMPROC)get_proc(load, "glLinkProgram");
    glad_glGetProgramiv = (PFNGLGETPROGRAMIVPROC)get_proc(load, "glGetProgramiv");
    glad_glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)get_proc(load, "glGetProgramInfoLog");
    glad_glDeleteShader = (PFNGLDELETESHADERPROC)get_proc(load, "glDeleteShader");
    glad_glUseProgram = (PFNGLUSEPROGRAMPROC)get_proc(load, "glUseProgram");
    glad_glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)get_proc(load, "glGetUniformLocation");
    glad_glUniform1i = (PFNGLUNIFORM1IPROC)get_proc(load, "glUniform1i");
    glad_glUniform1f = (PFNGLUNIFORM1FPROC)get_proc(load, "glUniform1f");
    glad_glUniform3f = (PFNGLUNIFORM3FPROC)get_proc(load, "glUniform3f");
    glad_glUniform3fv = (PFNGLUNIFORM3FVPROC)get_proc(load, "glUniform3fv");
    glad_glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)get_proc(load, "glUniformMatrix4fv");
    glad_glDrawArrays = (PFNGLDRAWARRAYSPROC)get_proc(load, "glDrawArrays");
    glad_glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)get_proc(load, "glDeleteVertexArrays");
    glad_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)get_proc(load, "glDeleteBuffers");
    
    return 1;
}
