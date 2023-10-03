import streamlit as st
import mysql.connector
import time
# Replace with your database credentials
db_config = {
    'host': 'localhost',
    'user': 'root',
    'password': 'tiger',
    'database': 'ultra',
}
conn = mysql.connector.connect(**db_config)
# Function to fetch data from MySQL
def fetch_data():
    cursor = conn.cursor()
    cursor.execute("SELECT state FROM ultra.distance")
    data = cursor.fetchall()
    cursor.close()
    return data

st.title("Streamlit App with MySQL Integration")

# Fetch data from MySQL
data = fetch_data()

# Create a horizontal layout for the colored boxes with numbers
st.write("<div style='display: flex;'>", unsafe_allow_html=True)

# Initialize a list to keep track of selected slots
selected_slots = []

# Display colored squares with numbers based on 'state' values
for i, row in enumerate(data):
    square_color = "red" if row[0] == 1 else "green"

    # Check if the slot is vacant (green) and allow selection
    if square_color == "green":
        is_selected = st.checkbox(f"Slot {i + 1}", key=f"checkbox_{i}")
        if is_selected:
            selected_slots.append(i + 1)

    st.markdown(
        f'<div style="background-color: {square_color}; width: 100px; height: 100px; margin: 10px; text-align: center;">{i + 1}</div>',
        unsafe_allow_html=True,
    )

# Close the horizontal layout
st.write("</div>", unsafe_allow_html=True)


# Close the MySQL connection when the app is done
conn.close()
time.sleep(5)
st.rerun()