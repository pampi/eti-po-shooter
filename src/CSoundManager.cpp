#include "headers.h"

CSoundManager::CSoundManager()
{
}

bool CSoundManager::play(const char *file, bool loop)
{
    SAudio *pAudio = new SAudio;

    pAudio->file = file;
    if(!pAudio->music.openFromFile(pAudio->file))
    {
        delete pAudio;
        return false;
    }

    pAudio->music.setLoop(loop);
    pAudio->music.play();
    playlist.push_back(pAudio);

    return true;
}

bool CSoundManager::stop(const char *file, bool all)
{
    bool ret_val = false;
    std::string filename=file;
    SAudio *pAudio;

    for(std::list<SAudio *>::iterator i=playlist.begin(); i!=playlist.end(); i++)
    {
        pAudio = *playlist.begin();
        if(pAudio->file.compare(filename)==0)
        {
            ret_val=true;

            //zatrzymanie odtwarzania pliku
            if(pAudio->music.getStatus() != sf::SoundSource::Stopped)
                pAudio->music.stop();

            //zwalnianie pamięci
            delete pAudio;

            //usuwanie z playlisty
            if(!all)
            {
                playlist.erase(i);
                break;
            }
            else
            {
                std::list<SAudio *>::iterator tmp=i;
                i--;
                playlist.erase(tmp);
            }
        }
    }

    return ret_val;
}

void CSoundManager::stopAll()
{
    while(!playlist.empty())
    {
        SAudio *pAudio = *playlist.begin();

        if(pAudio->music.getStatus() != sf::SoundSource::Stopped)
            pAudio->music.stop();

        delete pAudio;
        playlist.pop_front();
    }
}
