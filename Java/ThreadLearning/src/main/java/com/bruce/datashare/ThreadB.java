package com.bruce.datashare;

/**
 * Created by bruce on 16-12-8.
 */
public class ThreadB extends  Thread {
    private  ThreadSafeWithOnlyPrivateVar numRef;

    public ThreadB(ThreadSafeWithOnlyPrivateVar num) {
        numRef = num;
    }

    @Override
    public void run() {
        super.run();
        numRef.addI("b");
    }
}
