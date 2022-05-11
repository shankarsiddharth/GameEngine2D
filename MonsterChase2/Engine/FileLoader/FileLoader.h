#pragma once

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include "../../GLib/GLib.h"

namespace FileLoader
{
	void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);

	GLib::Sprite* CreateSprite(const char* i_pFilename, unsigned int& o_Width, unsigned int& o_Height, unsigned int& o_Depth);

}
