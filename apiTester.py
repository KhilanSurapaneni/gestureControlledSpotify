import spotipy
from spotipy.oauth2 import SpotifyOAuth

# Set up your Spotify credentials
client_id = 'be993bd5270340218be21d86d9e0361d'
client_secret = 'beeaf5111ddf498fa7c52493e69b3799'
redirect_uri = 'http://localhost:8080/callback'
scope = 'user-read-currently-playing'

# Authorization
auth_manager = SpotifyOAuth(client_id, client_secret, redirect_uri, scope=scope)
sp = spotipy.Spotify(auth_manager=auth_manager)

# Getting the current song
current_track = sp.current_user_playing_track()
if current_track is not None:
    track_name = current_track['item']['name']
    artist_name = current_track['item']['artists'][0]['name']
    print(f"Currently Selected Song: {track_name} by {artist_name}")
else:
    # Fetch the recently played track if nothing is currently playing
    recently_played = sp.current_user_recently_played(limit=1)
    if recently_played['items']:
        last_track = recently_played['items'][0]['track']
        track_name = last_track['name']
        artist_name = last_track['artists'][0]['name']
        print(f"Most recently played: {track_name} by {artist_name}")
    else:
        print("No recent playback information found.")
