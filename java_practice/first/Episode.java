class Episode {
    int seriesNumber;
    int episodeNumber;

    void skipIntro() {
        System.out.println("Skipping into....");
    }

    void skipToNext() {
        System.out.println("Loading next episode...");
    }
}

class EpisodeTestDrive{
    public static void main(String[] args){
        Episode episode = new Episode();
        episode.seriesNumber = 1;
        episode.episodeNumber = 2;

        episode.skipIntro();
        episode.skipToNext();

        System.out.println("Series: " + episode.seriesNumber);
        System.out.println("Episode: " + episode.episodeNumber);

    }
}