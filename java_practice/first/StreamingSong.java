class StreamingSong {
	String title;
	String artist;
	int duration;

	void play() {
		System.out.println("playing song");
	}

	void printDetails() {
		System.out.println("This is " + title + " by " + artist);
	}
}

class StreamingSongTestDrive {
	public static void main(String[] args){
		StreamingSong song = new StreamingSong();
		song.title = "Song Title";
		song.artist = "Artist Name";
		song.duration = 300;

		song.play();
		song.printDetails();
		System.out.println("Duration: " + song.duration + " seconds");
		System.out.println("Title: " + song.title);
		System.out.println("Artist: " + song.artist);
		System.out.println("Playing: " + song.title + " by " + song.artist);
		System.out.println("Duration: " + song.duration + " seconds");
		System.out.println("Playing: " + song.title + " by " + song.artist);
		System.out.println("Duration: " + song.duration + " seconds");
	}
}
