package dao.entity;

public class Custormer {
    private int custormer_id;
    private String contact_name;
    private String phone;
    private String address;
    // getter&setter
    public int getCustormer_id() {
        return custormer_id;
    }

    public void setCustormer_id(int custormer_id) {
        this.custormer_id = custormer_id;
    }

    public String getContact_name() {
        return contact_name;
    }

    public void setContact_name(String contact_name) {
        this.contact_name = contact_name;
    }

    public String getPhone() {
        return phone;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }
}
