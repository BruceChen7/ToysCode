package com.bruce.datashare;

/**
 * Created by bruce on 16-12-8.
 */
public class TestThreadSafeWithOnlyPrivateVar {
    public static void main(String[] args) {
        ThreadSafeWithOnlyPrivateVar num = new ThreadSafeWithOnlyPrivateVar();
        // Both myThreadA and myThreadB share the same num;
        // But TestThreadSafeWithOnlyPrivateVar only has private variable
        // so it's thread safe
        ThreadA myThreadA = new ThreadA(num);
        ThreadB myThreadB = new ThreadB(num);

        myThreadA.start();
        myThreadB.start();
    }

}
