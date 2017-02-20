package com.itsm.collecting.service;

/**
 * Created by bruce on 17-2-20.
 */
public interface IDirectQueueConsumeTask {
        public void consume(byte[] data);
}
