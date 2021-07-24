#ifndef _MYLINKEDLIST_
#define _MYLINKEDLIST_

#include<stdbool.h>

typedef struct Song{
	int id;						
	char *filename;				
	int time_in_seconds;		
	char *artist;
	char *genre;
	char *title;
	char *album;
	int bitrate;
} Song;

//Getters
int getId(Song *s);
char* getFilename(Song *s);
int getLength(Song *s);
char* getArtist(Song *s);
char* getGenre(Song *s);
char* getAlbum(Song *s);
char* getTitle(Song *s);
int getBitrate(Song *s);
//Setters
bool setFilename(char *name, Song *s);
bool setTime(int time, Song *s);
bool setId(int id, Song *s);
bool setArtist(char *artist_t, Song *s);
bool setGenre(char *genre_t, Song *s);
bool setAlbum(char *name, Song *s);
bool setTitle(char *title_t, Song *s);
bool setBitrate(int bitrate_t, Song *s);
//Funcs
Song *createSong(char *fname, int time);
bool deleteSong(Song *s);

typedef struct MusicPlayer{
	int q_sz;
	int curr;
	int loop_song;
	int loop_queue;
	int shuffle_on;
	int volume;
	int status;
	char *curPlaylist;
	Song* queue;
	int speed;
	long long q_length;
} MusicPlayer;

//Basic functions
MusicPlayer* initPlayer();
bool addSong(Song s, MusicPlayer *mp);
bool addQueue(int n, Song *s, MusicPlayer *mp);

int getCurr(MusicPlayer *mp);
long long getQLength(MusicPlayer *mp);
int getQSize(MusicPlayer *mp);
int getVolume(MusicPlayer *mp);
Song* nowPlaying(MusicPlayer *mp);
Song* getQueue(MusicPlayer *mp);

bool setQSize(int sz, MusicPlayer *mp);
bool setVolume(int vol, MusicPlayer *mp);
bool setSpeed(int speed, MusicPlayer *mp);

int loopCurrent(MusicPlayer *mp);
int loopQueue(MusicPlayer *mp);
bool seek(int t, MusicPlayer *mp);
int skipNext(MusicPlayer *mp);
int gotoPrev(MusicPlayer *mp);
bool setCurr(int c, MusicPlayer *mp);
int pause(MusicPlayer *mp);
int play(MusicPlayer *mp);
int stop(MusicPlayer *mp);
bool clearQueue(MusicPlayer *mp);
bool shuffle(MusicPlayer *mp);
void rickRoll(MusicPlayer *mp);
bool removeFromQueue(Song s, MusicPlayer *mp);
bool filterBy(int param, MusicPlayer *mp);
bool sortBy(int param, int type, MusicPlayer *mp);

void printNowPlaying(MusicPlayer *mp);

bool loadPlaylist(char *name, MusicPlayer *mp);
bool createPlaylist(char *name, MusicPlayer *mp);

bool destructPlayer(MusicPlayer **mp);
#endif