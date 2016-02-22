package com.bruce.observer;

/**
 * Created by bruce on 2016/2/22.
 */
public interface Observer {
    //观察者的接口，用来更新关注的状态
    public void update(Subject subject);
}
