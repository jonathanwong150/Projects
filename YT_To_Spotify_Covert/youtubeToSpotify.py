import spotipy
import spotipy.util as util
import youtube_dl

def youtubeToSpotify():
    # Input your custom username and information below
    YOUTUBE_USERNAME = "YOUR_YOUTUBE_USERNAME"
    SPOTIFY_USERNAME = "YOUR_SPOTIFY_USERNAME"
    SPOTIFY_CLIENT_ID = "YOUR_SPOTIFY_CLIENT_ID"
    SPOTIFY_CLIENT_SECRET = "YOUR_SPOTIFY_CLIENT_SECRET"
    SPOTIFY_REDIRECT_URI = "YOUR_SPOTIFY_REDIRECT_URI"

    # Open Youtube client with your username
    ydl_opts = {
    "username": YOUTUBE_USERNAME,
    "quiet": True
    }

    # Set up Spotify client with user information
    token = util.prompt_for_user_token(SPOTIFY_USERNAME, scope="user-library-modify", client_id=SPOTIFY_CLIENT_ID,
    client_secret=SPOTIFY_CLIENT_SECRET, redirect_uri=SPOTIFY_REDIRECT_URI)
    sp = spotipy.Spotify(auth=token)

    # Use YoutubeDL library to extract information about the users liked videos
    with youtube_dl.YoutubeDL(ydl_opts) as ydl:
        liked_videos = ydl.extract_info("ytuser:{}/likes".format(YOUTUBE_USERNAME), download=False)

    # Iterate through each video extracted by ydl and find song and artist
    for video in liked_videos:
        song_title = video["title"]
        artist = video["uploader"]
        results = sp.search(q="artist:{} track:{}".format(artist, song_title), type="track")

        # If the song is found, add it to the user's library
        if len(results["tracks"]["items"]) > 0:
            song_id = results["tracks"]["items"][0]["id"]
            sp.current_user_saved_tracks_add([song_id])

    print("Finished adding liked songs from Youtube to Spotify.")