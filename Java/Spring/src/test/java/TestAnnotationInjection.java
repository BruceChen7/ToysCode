import com.bruce.learn.di.CDPlayerConfig;
import com.bruce.learn.di.ICompactDisc;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;
import static org.junit.Assert.*;

/**
 * Created by bruce on 16-11-8.
 */

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(classes = CDPlayerConfig.class)
public class TestAnnotationInjection {
    @Autowired
    private ICompactDisc cd;

    @Test
    public void testCdShouldNotNull() {
        assertNotNull(cd);
        cd.play();

    }
}
