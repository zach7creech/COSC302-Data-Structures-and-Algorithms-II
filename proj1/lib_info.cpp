#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

/* Nicholas Creech, Zachery Creech
 * Project 1: Create a program that reads a file containing MP3 tracks
 * and prints the tracks out sorted by artist, album, and track number
 * 1/20/20
 */

using namespace std;

string fixSpaces(const string&); //Removes underscores and replaces with spaces
string secondsToTime(int); //Converts a number of seconds to mm:ss format

struct Song
{
	string title;
	int track;
	string time;
};

struct Album
{
	map<int, Song> songs;
	string name;
	string genre;
	int seconds;
	int totalTracks;
};

struct Artist
{
	map<string, Album> albums;
	string name;
	int seconds;
	int totalTracks;
};

int main(int argc, char ** argv)
{
	map<string, Artist> all_artists; //For all artists
	map<string, Artist>::iterator artist_itr;
	map<string, Album>::iterator album_itr; //For generic album
	map<int, Song>::iterator song_itr; //For generic song
	
	const string padding8 = "        "; //Padding for printing

	ifstream fin;
	stringstream ss, stoi;

	//Error-check runtime arguments
	if(argc != 2)
	{
		cout << "Usage: ./lib_info <file>\n";
		return 1;
	}

	//Begin reading in from file, one line at a time	
	fin.open(argv[1]);
	
	string line;
	while(getline(fin, line))
	{
		Artist artist;
		Album album;
		Song song;
		
		string time; //for splitting minutes/seconds
		int min, sec, delim;
		
		//Read line from file and store in respective structs
		ss.clear();
		ss.str(line);
		ss >> song.title >> time >> artist.name >> album.name >> album.genre >> song.track;

		//Remove underscores from names
		song.title = fixSpaces(song.title);
		artist.name = fixSpaces(artist.name);
		album.name = fixSpaces(album.name);
		album.genre = fixSpaces(album.genre);
		
		//fixing time to be usable minutes and seconds
		delim = time.find(':');
		stoi.clear();
		stoi.str(time.substr(0, delim));
		stoi >> min;
		stoi.clear();
		stoi.str(time.substr(delim + 1));
		stoi >> sec;
		song.time = time;

		//Check if artist exists
		artist_itr = all_artists.find(artist.name);
		
		//if artist doesn't exist then everything can just be assigned
		if(artist_itr == all_artists.end())
		{
			album.songs[song.track] = song;
			album.seconds = (min * 60) + sec;
			album.totalTracks = 1;
			artist.albums[album.name] = album;
			artist.seconds = (min * 60) + sec;
			artist.totalTracks = 1;
			all_artists[artist.name] = artist;
		}
		//otherwise artist already exists and needs to be updated
		else
		{
			//update artist's total time
			artist_itr->second.seconds += (min * 60) + sec;
			artist_itr->second.totalTracks++;

			//Check if album exists
			album_itr = artist_itr->second.albums.find(album.name);

			//if album doesn't exist then everything can just be assigned
			if(album_itr == artist_itr->second.albums.end())
			{
				album.seconds = (min * 60) + sec;
				album.songs[song.track] = song;
				album.totalTracks = 1;
				artist_itr->second.albums[album.name] = album;
			}
			//otherwise album already exists and needs to be updated
			else
			{
				album_itr->second.seconds += (min * 60) + sec;
				album_itr->second.songs[song.track] = song;
				album_itr->second.totalTracks++;
			}
		}
	}
	
	fin.close();

	//Begin printing formatted list, starting with each artist
	for(artist_itr = all_artists.begin(); artist_itr != all_artists.end(); artist_itr++)
	{
		Artist* currArtist = &artist_itr->second;
		cout << currArtist->name << ": " << currArtist->totalTracks << ", " << secondsToTime(currArtist->seconds) << endl;

		//Print all albums for current artist
		for(album_itr = currArtist->albums.begin(); album_itr != currArtist->albums.end(); album_itr++)
		{
			Album* currAlbum = &album_itr->second;
			cout << padding8 << currAlbum->name << ": " << currAlbum->totalTracks << ", " << secondsToTime(currAlbum->seconds) << endl;

			//Print all songs for current album
			for(song_itr = currAlbum->songs.begin(); song_itr != currAlbum->songs.end(); song_itr++)
			{
				Song* currSong = &song_itr->second;
				cout << padding8 << padding8 << currSong->track << ". " << currSong->title << ": " << currSong->time << endl; 
			}
		}
	}
	
	return 0;
}

//Remove underscores and replaces with spaces
string fixSpaces(const string& orig)
{
	string result = "";

	for(unsigned int x = 0; x < orig.length(); x++)
	{
		if(orig[x] == '_')
			result += ' ';
		else
			result += orig[x];
	}

	return result;
}

//Converts a number of seconds to mm:ss format
string secondsToTime(int sec)
{
	stringstream ss;

	ss.str("");

	if(sec < 60)
	{
		if(sec < 10)
			ss << "0:0" << sec;
		else
			ss << "0:" << sec;
	}

	else
	{
		int min = (sec - (sec % 60)) / 60;

		if(sec - (min * 60) >= 10)
			ss << min << ":" << (sec - (min * 60));
		else
			ss << min << ":0" << (sec - (min * 60));
	}

	return ss.str();
}
