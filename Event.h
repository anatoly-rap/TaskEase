class Event {
public:
    explicit Event(const char* date);
    explicit Event(const std::string& date);
    Event(const Event& other);
    Event& operator=(const Event& other);
    ~Event();
    void set(int year, int month, int day);
    int year() const;
    int month() const;
    int day() const;
    std::string toString() const;
    bool operator==(const Event& other) const;
private:
    int m_year;
    int m_month;
    int m_day;
};
std::ostream& operator<<(std::ostream& os, const Event& event);
#endif // EVENT_H
