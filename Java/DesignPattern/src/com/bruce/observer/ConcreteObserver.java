package com.bruce.observer;

/**
 * Created by bruce on 2016/2/22.
 */
public class ConcreteObserver  implements Observer {


    @Override
    public void update(Subject subject) {
        subject.getSubjectStatus();
    }
}
