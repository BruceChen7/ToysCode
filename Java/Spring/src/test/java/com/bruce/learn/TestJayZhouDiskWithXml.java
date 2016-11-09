package com.bruce.learn;

import com.bruce.learn.di.JayZhouDisc;
import org.junit.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

/**
 * Created by bruce on 16-11-9.
 */
public class TestJayZhouDiskWithXml {


    @Test
    public void testXmlInject() {
        ApplicationContext ctx = new ClassPathXmlApplicationContext("classpath:DiscXmlConfig.xml");
        JayZhouDisc disc = ctx.getBean(JayZhouDisc.class);
        disc.play();

    }
}
