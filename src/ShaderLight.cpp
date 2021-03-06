#include "ShaderLight.hpp"
#include "OpenGLErrorHandler.hpp"
#include <string.h>    //   für  strcpy  und  strcat

/*
 *  Die Methode versorgt das Shaderprogramm mit Werten, die
 *  im Parameter  properties  bereitgestellt werden.
 *  Der Verwendung dieser Methode muss der einmalige Aufruf
 *  der Methode  readAddresses  vorausgehen.
 */
void ShaderLight::installProperties(LightProperties &properties) {
    glUniform4fv(position, 1, properties.position);
      OpenGLErrorHandler::checkAndReportErrors("set light ambient color"); 
    glUniform4fv(ambientColor, 1, properties.ambientColor);
      OpenGLErrorHandler::checkAndReportErrors("set light ambient color");
    glUniform4fv(diffuseColor, 1, properties.diffuseColor);
      OpenGLErrorHandler::checkAndReportErrors("set light diffuse color");
    glUniform4fv(specularColor, 1, properties.specularColor);
      OpenGLErrorHandler::checkAndReportErrors("set light specular color");
    glUniform1i(isFixed, properties.isFixed ? 1 : 0);
      OpenGLErrorHandler::checkAndReportErrors("set fixed ligth");
    glUniform1i(isOn, properties.isOn ? 1 : 0);
      OpenGLErrorHandler::checkAndReportErrors("switch ligth on");
}

/*
 *  Die Methode ermittelt die Adressen der im Vertex Shader
 *  vereinbarten Programmparameter.
 *  sourceName  ist der Name der Lichtquelle, so wie er in der
 *  Variablenvereinbarung im Vertexshader vorkommt. Gegenwärtig
 *  verwendete Werte sind "light0"  und "light1".
 *
 *  Aufruf in  ShaderInterface::queryAdresses().
 */
void ShaderLight::readAddresses(GLuint shaderProgram, const GLchar *sourceName) {
    ambientColor = readAddress(shaderProgram, sourceName, ".ambientColor");
    diffuseColor = readAddress(shaderProgram, sourceName, ".diffuseColor");
    specularColor = readAddress(shaderProgram, sourceName, ".specularColor");
    position = readAddress(shaderProgram, sourceName, ".position");
    isOn = readAddress(shaderProgram, sourceName, ".isOn");
    isFixed = readAddress(shaderProgram, sourceName, ".isFixed");
}

/*
 *  Die Methode bildet aus dem Namen der Lichtquelle und dem Namen
 *  eines Attributs der Lichtqulle den vollständigen Attributnamen
 *  und ermittelt die Adresse des Attributs im Shaderprogramm.
 */
GLint ShaderLight::readAddress(GLuint shaderProgram,
                                 const GLchar *sourceName,
                                 const GLchar *varName) {
    GLint result;
    GLchar dest[strlen(sourceName) + strlen(varName) + 2];
    strcpy(dest, sourceName);
    strcat(dest, varName);

    result = glGetUniformLocation(shaderProgram, dest);
    OpenGLErrorHandler::checkAndReportErrors("glGetUniformLocation light prop"); 
    return result;
}
