package com.bruce.datashare;

/**
 * Created by bruce on 16-12-8.
 */
public class ThreadA  extends  Thread {
    private ThreadSafeWithOnlyPrivateVar numRef;
    public ThreadA(ThreadSafeWithOnlyPrivateVar num) {
        numRef = num;
    }

    @Override
    public void run() {
        super.run();
        numRef.addI("a");
    }


}
