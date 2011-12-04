using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace JustServer.LoggerUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Initialized(object sender, EventArgs e)
        {
            List<EventType> eventTypes = new List<EventType>()
            {
                new EventType() { ID = 0, Name = "Все события" }
            };

            using (JustServerLogEntities dbContext = new JustServerLogEntities())
            {
                eventTypes.AddRange(dbContext.EventTypes);
                EventTypesCombobox.ItemsSource = eventTypes;
                EventTypesCombobox.SelectedIndex = 0;

                List<Event> events = dbContext.Events.Include("EventType").ToList();
                EventsGrid.ItemsSource = events;
            }
        }

        private void EventTypesCombobox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            RefreshEventsList();
        }

        private void DateFrom_SelectedDateChanged(object sender, SelectionChangedEventArgs e)
        {
            RefreshEventsList();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            RefreshEventsList();
        }

        private void DateTo_SelectedDateChanged(object sender, SelectionChangedEventArgs e)
        {
            RefreshEventsList();
        }

        private void RefreshEventsList()
        {
            EventType selectedEventType = EventTypesCombobox.SelectedItem as EventType;

            using (JustServerLogEntities dbContext = new JustServerLogEntities())
            {
                IEnumerable<Event> events = dbContext.Events.Include("EventType");

                if (selectedEventType.ID != 0)
                {
                    events = events.Where(e => e.EventTypeID == selectedEventType.ID);
                }

                if (DateFrom.SelectedDate != null)
                {
                    events = events.Where(e => e.EventTime.Date >= DateFrom.SelectedDate.Value.Date);
                }

                if (DateTo.SelectedDate != null)
                {
                    events = events.Where(e => e.EventTime.Date <= DateTo.SelectedDate.Value.Date);
                }

                EventsGrid.ItemsSource = events.ToList();
            }
        }
    }
}
