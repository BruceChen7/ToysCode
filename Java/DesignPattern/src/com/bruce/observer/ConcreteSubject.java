package com.bruce.observer;
import  java.util.List;
import java.util.ArrayList;

/**
 * Created by bruce on 2016/2/22.
 */
public class ConcreteSubject implements  Subject {

    private  List<Observer> observers_ = new ArrayList<Observer>();
    private  String concreate_status_ = "";

    @Override
    public void addObserver(Observer observer) {
        observers_.add(observer);
    }


    @Override
    public void deleteObserver(Observer observer) {
        observers_.remove(observer);
    }

    @Override
    public void notifyAllObservers() {
        for(Observer observer : observers_) {
            observer.update(this);
        }
    }

    @Override
    public void getSubjectStatus() {
        System.out.println("Get Subject status " + concreate_status_);
    }

    public void setConcreateStatus(String status) {
        concreate_status_ = status;
    }



}
