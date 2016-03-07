package com.bruce.factory;

/**
 * Created by CM on 2016/3/7.
 */
public class BMW523Factory implements BMWFactory {


    @Override
    public BMW createBMW() {
        return new BMW523();
    }
}
