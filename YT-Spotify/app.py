import secrets
from googleapiclient.discovery import build
from flask import Flask, render_template, request, redirect, url_for, flash
import spotipy
import config
from spotipy.oauth2 import SpotifyOAuth

app = Flask(__name__)
app.secret_key = secrets.token_hex(16)

# Fetch YouTube Playlist
def fetch_youtube_playlist(api_key, playlist_id):
    youtube = build('youtube', 'v3', developerKey=api_key)
    request = youtube.playlistItems().list(
        part="snippet",
        maxResults=50,
        playlistId=playlist_id
    )
    response = request.execute()
    songs = []
    for item in response['items']:
        title = item['snippet']['title']
        songs.append(title)
    return songs

# Spotify Authentication
def spotify_authenticate(client_id, client_secret, redirect_uri):
    sp = spotipy.Spotify(auth_manager=SpotifyOAuth(client_id=client_id,
                                                   client_secret=client_secret,
                                                   redirect_uri=redirect_uri,
                                                   scope="user-library-modify user-library-read"))
    return sp


# Like Songs on Spotify and collect their details
def like_songs_on_spotify(sp, songs):
    added_songs = []
    not_added_songs = []
    for song in songs:
        results = sp.search(q=song, limit=1)
        if results['tracks']['items']:
            track = results['tracks']['items'][0]
            track_id = track['id']

            # Check if the song is already liked
            is_liked = sp.current_user_saved_tracks_contains(tracks=[track_id])[0]
            if not is_liked:
                sp.current_user_saved_tracks_add(tracks=[track_id])
                added_songs.append({
                    'cover_url': track['album']['images'][0]['url'],
                    'name': track['name'],
                    'artist': track['artists'][0]['name']
                })
            else:
                not_added_songs.append({
                    'cover_url': track['album']['images'][0]['url'],
                    'name': track['name'],
                    'artist': track['artists'][0]['name']
                })

    return added_songs, not_added_songs

@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')

@app.route('/convert', methods=['POST'])
def convert():
    playlist_url = request.form.get('playlist_url')
    if not playlist_url:
        flash("Please enter a YouTube playlist URL.")
        return redirect(url_for('index'))

    # Extract playlist_id from the URL
    playlist_id = playlist_url.split("list=")[-1]

    # Fetch songs from YouTube
    youtube_songs = fetch_youtube_playlist(config.api_key, playlist_id)

    # Authenticate with Spotify
    sp = spotify_authenticate(config.client_id, config.client_secret, config.redirect_uri)

    # Like songs on Spotify and get their details
    added_songs, not_added_songs = like_songs_on_spotify(sp, youtube_songs)

    return render_template('success.html', added_songs=added_songs, not_added_songs=not_added_songs)

if __name__ == '__main__':
    app.run()
