package com.bruce.factory;

/**
 * Created by CM on 2016/3/7.
 */
public class Client {
    private BMWFactory bmw_factory_;

    public BMW getBMW(int type) {
        switch (type) {
            case 320:
                bmw_factory_ = new BMW320Factory();
                return bmw_factory_.createBMW();
            case 523:
                bmw_factory_ = new BMW523Factory();
                return bmw_factory_.createBMW();
            default:
                return null;

        }
    }

    public static void main(String[] args){

        Client client = new Client();

        BMW car_320 = client.getBMW(320);

        BMW car_523 = client.getBMW(523);
    }
}
