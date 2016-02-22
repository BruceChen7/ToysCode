package com.bruce.observer;

/**
 * Created by bruce on 2016/2/22.
 */
public interface Subject {
    //添加一个观察者
    public  void addObserver(Observer observer);

    //删除一个观察者
    public void deleteObserver(Observer observer);

    //通知所有的观察者
    public void notifyAllObservers();

    //获取主题的状态
    public void getSubjectStatus();

}
