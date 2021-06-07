import java.beans.PropertyEditorSupport;

public class StaticTextEditor extends PropertyEditorSupport
{
    protected String name;

    @Override
    public String[] getTags() {
        return new String[]{"static text", "text", "string", "value", "component"};
    }

    @Override
    public void setAsText(String str) {
        this.name = str;
        super.setAsText(str);
    }

    @Override
    public String getJavaInitializationString() {
        return "\" " + name + "\"";
    }
}
