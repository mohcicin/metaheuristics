#include "Define.h"
#include <unistd.h>

void fprints(FILE *file, const char* object, const char* _class) {
    fprintf(file, "/*--------------------------------*- C++ -*----------------------------------*\\ \n");
    fprintf(file, "| =========                 |                                                 | \n");
    fprintf(file, "| \\\\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           | \n");
    fprintf(file, "|  \\\\    /   O peration     | Version:  2.1.1                                 | \n");
    fprintf(file, "|   \\\\  /    A nd           | Web:      www.OpenFOAM.com                      | \n");
    fprintf(file, "|    \\\\/     M anipulation  | Author:   tieuminh2510@gmail.com                | \n");
    fprintf(file, "\\*---------------------------------------------------------------------------*/ \n");
    fprintf(file, "FoamFile                                                                        \n");
    fprintf(file, "{                                                                               \n");
    fprintf(file, "    version     2.0;                                                            \n");
    fprintf(file, "    format      ascii;                                                          \n");
    fprintf(file, "    class       %s;\n", _class);
    fprintf(file, "    object      %s;\n", object);
    fprintf(file, "}                                                                               \n");
    fprintf(file, "// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * // \n");
    fprintf(file, "\n");    
}

void fprinte(FILE *file) {
    fprintf(file, "\n");
    fprintf(file, "// ************************************************************************* // \n");
    fclose(file);
}

int createFolder(const char* foldername) {
    char command[1024];
    strcpy(command, "mkdir ");
    strcat(command, foldername);
    return system(command);
}

int moveData(const char* from, const char* to) {
    char command[1024];
    strcpy(command, "mv -f ");
    strcat(command, from);
    strcat(command, " ");
    strcat(command, to);
    return system(command);
}

int changeFolder(const char* folderame) {
    char folderName[256];
    strcpy(folderName,"./");
    strcat(folderName,folderame); 
    return chdir(folderName);
}
int removeData(const char* folder) {
    char command[1024];
    strcpy(command, "rm -rf ");
    strcat(command, folder);
    return system(command);
}

int runCase(const char* _command) {
    char command[1024];
    strcpy(command, _command);
    strcat(command, " > " );
    strcat(command, _command);
    strcat(command, ".log 2>&1");    
    return system(command);
}
int catchCase(const char* data) {
    char command[1024];
    strcpy(command, "echo '"); 
    strcat(command, data);
    strcat(command, "' >> .foam");    
    return system(command);
}

int testCase(const char* _command) {
    char command[1024];
    strcpy(command, _command);
    strcat(command, " > " );
    strcat(command, "testCase.log 2>&1");    
    return system(command);
}

int runCase(const char* _command, unsigned int nodes) {
    char command[1024];        
    if(nodes > 1) {
        runCase("decomposePar");
        strcpy(command,"mpirun -np ");          
        char node[4];           
        sprintf(node,"%d", nodes);
        strcat(command, node);
        strcat(command, " ");
        strcat(command, _command);
        strcat(command, " -parallel > "); 
        strcat(command, _command);
        strcat(command, ".log 2>&1");   
        return system(command);
    }   
    else {
        return runCase(_command);
    }   
}

bool findValue(const char* filename, const char* value) {
    bool result = false;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        if(!line.compare(value))
            result =  true;
    }
    file.close();
    return result;
}

void writeLog(const char* logFile, string content) {
    ofstream file;
    file.open(logFile, ios_base::app);
    file << content; 
    file.close();
}

unsigned int a2i(char character) {
    return character - 48;
}
