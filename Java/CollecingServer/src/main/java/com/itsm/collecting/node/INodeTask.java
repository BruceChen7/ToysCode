package com.itsm.collecting.node;

import java.io.IOException;
import java.util.concurrent.TimeoutException;

/**
 * Created by bruce on 16-12-13.
 */
public interface INodeTask {
    void startMasterTask();
    void startSlaveTask();
}
