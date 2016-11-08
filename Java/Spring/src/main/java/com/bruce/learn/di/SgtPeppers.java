package com.bruce.learn.di;

/**
 * Created by bruce on 16-11-8.
 */
@Component
public class SgtPeppers implements  ICompactDisc {
    private final String title  = "稻花香";
    private final String artist = "周杰伦";

    public void play() {
        System.out.println("playing " + title + " by " + artist);
    }
}
