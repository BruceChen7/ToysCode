package com.itsm.collecting.util;

import java.io.*;

/**
 * Created by CM on 2016/7/21.
 */
public class Serializer {

    public static byte[] serialize(Object obj) throws IOException {

        ByteArrayOutputStream b = new ByteArrayOutputStream();
        try {

            try {
                ObjectOutputStream o = new ObjectOutputStream(b);
                o.writeObject(obj);
            } catch (Exception e) {
                e.printStackTrace();
            }
            return b.toByteArray();
        } catch (Exception e) {
            e.printStackTrace();

        }
        return b.toByteArray();
    }

    public static Object deserialize(byte[] bytes) throws IOException, ClassNotFoundException {


        try {
            ByteArrayInputStream b = new ByteArrayInputStream(bytes);

            try {
                ObjectInputStream o = new ObjectInputStream(b);
                return o.readObject();

            } catch (Exception e) {
                e.printStackTrace();
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            return null;
        }
    }

}