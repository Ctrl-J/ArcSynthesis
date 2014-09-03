#pragma once
/// Number of keys to map to the key state buffers (256 in Win32)
#define KEY_COUNT 256

// Obvious include for a Win32 application
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>

// OpenGl
#include <gl\GL.h>
#include <GLEXT\glext.h>
#include <GLEXT\wglext.h>

// GLM for math functions! And the constants header (mainly for pi)
#include <GLM\glm.hpp>
#include <GLM\gtc\constants.hpp>
#include <GLM\gtc\type_ptr.hpp>

// RapidXML for loading of config files and shaders
#include <RapidXML\rapidxml.hpp>
#include <RapidXML\rapidxml_utils.hpp>

// Basic stream manipulation, memory (for c++11 smart pointers), and basic data structures.
#include <array>
#include <ctime>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <map>
#include <vector>

#include <ArcSynth/Win32/glextensions.h>