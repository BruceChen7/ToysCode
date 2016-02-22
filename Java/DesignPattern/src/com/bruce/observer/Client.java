package com.bruce.observer;

/**
 * Created by bruce on 2016/2/22.
 */
public class Client {
    public  static void main(String[] args) {
        ConcreteObserver observer = new ConcreteObserver();
        ConcreteObserver another_observer = new ConcreteObserver();

        ConcreteSubject subject = new ConcreteSubject();
        subject.addObserver(observer);
        subject.addObserver(another_observer);

        subject.setConcreateStatus("1");
        subject.notifyAllObservers();

        subject.setConcreateStatus("2");
        subject.notifyAllObservers();
    }
}
