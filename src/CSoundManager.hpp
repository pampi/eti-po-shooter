#ifndef CSOUNDMANAGER_H
#define CSOUNDMANAGER_H

#include "headers.h"

/*
 *  TO DO:
 *  odtwarzanie dźwięków załadaowanych do RAMu
 */

//Menedżer odtwarzania plików audio
class CSoundManager
{
private:
    struct SAudio
    {
        std::string file;
        sf::Music music;
    };

    std::list<SAudio *> playlist;
public:
    CSoundManager();

    //Odtwarza muzykę z pliku
    bool play(const char* file, bool loop);
    //Zatrzymuje określoną muzykę z pliku
    bool stop(const char* file, bool all=false);
    //Zatrzymaj wszelaką muzykę
    void stopAll();
};

#endif // CSOUNDMANAGER_H
