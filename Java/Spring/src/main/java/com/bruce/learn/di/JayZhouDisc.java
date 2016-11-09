package com.bruce.learn.di;

import org.springframework.stereotype.Component;

/**
 * Created by bruce on 16-11-9.
 */
@Component
public class JayZhouDisc implements ICompactDisc {
    private final String singer = "Jay Zhou";
    private final String songName = "青花瓷";

    public void play() {
        System.out.println("playing " + songName + " by " + singer);
    }
}
