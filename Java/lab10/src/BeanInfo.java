import java.beans.BeanDescriptor;
import java.beans.IntrospectionException;
import java.beans.PropertyDescriptor;
import java.beans.SimpleBeanInfo;

public class BeanInfo extends SimpleBeanInfo
{
    @Override

    public BeanDescriptor getBeanDescriptor() {

        return new BeanDescriptor(InterfaceBean.class);

    }

    /** This is a convenience method for creating PropertyDescriptor objects */

    static PropertyDescriptor prop(String name, String description) {

        try {

            PropertyDescriptor p = new PropertyDescriptor(name, InterfaceBean.class);

            p.setShortDescription(description);

            return p;

        }

        catch(IntrospectionException e) { return null; }

    }

    static PropertyDescriptor[] props = {

            prop("ButtonAddText", "add new record into list"),

            prop("StaticText", "Component static text"),
    };

    static {

        props[0].setPropertyEditorClass(SubmitButtonEditor.class);

        props[1].setPropertyEditorClass(StaticTextEditor.class);
    }

    @Override

    public PropertyDescriptor[] getPropertyDescriptors() { return props; }

    @Override

    public int getDefaultPropertyIndex() { return 0; }

}
