import javax.swing.event.TableModelListener;
import javax.swing.table.TableModel;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

class ModelTable implements TableModel {

    static final String[] columnNames = new String[]{"Номер", "Классификация", "Тип", "Наименование"};
    static final Class[] columnTypes = new Class[]{String.class, String.class, String.class, String.class, String.class, Integer.class, Integer.class};
    private Set<TableModelListener> listeners = new HashSet<TableModelListener>();
    private ArrayList<MonumentNode> infoNodes;

    public ModelTable() {
        infoNodes = new ArrayList<MonumentNode>();
    }

    public ModelTable(ArrayList<MonumentNode> al) {
        this.infoNodes = al;
    }

    public void setInfoArray(ArrayList<MonumentNode> al) {
        infoNodes = al;
    }

    public int getColumnCount() {
        return columnNames.length;
    }

    public int getRowCount() {
        return infoNodes.size();
    }

    public Class getColumnClass(int columnIndex) {
        return columnTypes[columnIndex];
    }

    public String getColumnName(int columnIndex) {
        return columnNames[columnIndex];
    }

    public Object getValueAt(int rowIndex, int columnIndex) {
        MonumentNode nb = infoNodes.get(rowIndex);
        switch (columnIndex) {
            case 0:
                return nb.getNumber();
            case 1:
                return nb.getType();
            case 2:
                return nb.getSpecies();
            case 3:
                return nb.getName();
        }
        return "";
    }

    @Override
    public void addTableModelListener(TableModelListener listener) {
        listeners.add(listener);
    }

    @Override
    public void removeTableModelListener(TableModelListener listener) {
        listeners.remove(listener);
    }

    @Override
    public boolean isCellEditable(int rowIndex, int columnIndex) {
        return false;
    }

    @Override
    public void setValueAt(Object value, int rowIndex, int columnIndex) {
    }
}

