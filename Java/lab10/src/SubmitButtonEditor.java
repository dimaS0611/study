import java.beans.PropertyEditorSupport;

public class SubmitButtonEditor extends PropertyEditorSupport {
    protected String name;

    @Override
    public String[] getTags() {
        return new String[]{"Submit","OK", "Add", "Update", "Add record"};
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
