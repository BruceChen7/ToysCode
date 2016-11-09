package com.bruce.learn;

import com.bruce.learn.di.CDPlayerConfig;
import com.bruce.learn.di.SgtPeppers;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

import static org.junit.Assert.assertNotNull;

/**
 * Created by bruce on 16-11-8.
 */

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(classes = CDPlayerConfig.class)
public class TestAnnotationInjection {
    /*
     * If SgtPeppers was replaced with ICompactDisc, there will be some problems
     * because thera are two classes for ICompactDisc, JayZhouDisc and SgtPeppers
     *
     */
    @Autowired
    private SgtPeppers cd;

    @Test
    public void testCdShouldNotNull() {
        assertNotNull(cd);
        cd.play();

    }
}
