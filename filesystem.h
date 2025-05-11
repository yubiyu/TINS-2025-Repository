#pragma once

#include <allegro5/allegro_physfs.h>
#include <physfs.h>

#include <iostream>

struct Filesystem
{
    static void Initialize(char **argv)
    {
        PHYSFS_init(argv[0]);
        if(PHYSFS_mount("./data.zip", "/", 1) == 0)
            std::cout << "Error - Filesystem: ./data.zip not found." << std::endl;
        else
            std::cout << "Filesystem: ./data.zip successfully mounted." << std::endl;
    }
    static void Uninitialize()
    {
        PHYSFS_deinit();
    }

    static void SetStandardFileInterface()
    {
        al_set_standard_file_interface();
    }
    static void SetPhysfsFileInterface()
    {
        al_set_physfs_file_interface();
    }
};
