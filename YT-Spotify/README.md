# YouTube to Spotify Playlist Converter

## Description

This project allows you to convert a YouTube playlist into your Spotify liked songs. It uses the YouTube Data API v3 and Spotify Web API to fetch playlist details and add songs to your Spotify account.

## Prerequisites

- Python 3.x
- pip (Python Package Installer)
- A YouTube Data API v3 Key
- A Spotify Developer Account with a registered App to get the Client ID, Client Secret, and Redirect URI

## Packages Used

- Flask
- google-api-python-client
- spotipy

## Installation

1. **Clone the Repository**

    ```
    git clone https://github.com/your-username/your-repo-name.git
    cd your-repo-name
    ```

2. **Install Required Packages**

    ```
    pip install Flask google-api-python-client spotipy
    ```

3. **Set Up Environment Variables**

    Create a file named `config.py` in the project directory and add your API keys and other credentials:

    ```python
    # config.py

    api_key = "YOUR_YOUTUBE_API_KEY"
    client_id = "YOUR_SPOTIFY_CLIENT_ID"
    client_secret = "YOUR_SPOTIFY_CLIENT_SECRET"
    redirect_uri = "YOUR_SPOTIFY_REDIRECT_URI"
    ```

4. **Run the Application**

    ```
    python app.py
    ```

    Open your web browser and go to `http://127.0.0.1:5000/` to use the application.
