#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

// Function to retrieve CPU information
void getCPUInfo(char* cpuInfo) {
    FILE* file = fopen("/proc/cpuinfo", "r");
    if (file) {
        fgets(cpuInfo, 1000, file);
        fclose(file);
    }
}

// Function to retrieve GPU information (you might need to adjust for your system)
void getGPUInfo(char* gpuInfo) {
    FILE* file = popen("lspci | grep -i VGA", "r");
    if (file) {
        fgets(gpuInfo, 1000, file);
        pclose(file);
    }
}

// Function to retrieve RAM amount
void getRAMInfo(char* ramInfo) {
    FILE* file = popen("free -h | awk 'NR==2 {print $2}'", "r");
    if (file) {
        fgets(ramInfo, 1000, file);
        pclose(file);
    }
}

// Function to retrieve system uptime
void getUptime(char* uptime) {
    FILE* file = popen("uptime -p", "r");
    if (file) {
        fgets(uptime, 1000, file);
        pclose(file);
    }
}

// Function to retrieve kernel version
void getKernelVersion(char* kernelVersion) {
    FILE* file = popen("uname -r", "r");
    if (file) {
        fgets(kernelVersion, 1000, file);
        pclose(file);
    }
}

// Callback function for "Close" button clicked event
void on_close_clicked(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    char cpuInfo[1000], gpuInfo[1000], ramInfo[1000], uptime[1000], kernelVersion[1000];

    // Checking if CLI mode is requested
    if (argc > 1 && strcmp(argv[1], "-cli") == 0) {
        getCPUInfo(cpuInfo);
        getGPUInfo(gpuInfo);
        getRAMInfo(ramInfo);
        getUptime(uptime);
        getKernelVersion(kernelVersion);

        printf("CPU Info: %s\n", cpuInfo);
        printf("GPU Info: %s\n", gpuInfo);
        printf("RAM Amount: %s\n", ramInfo);
        printf("System Uptime: %s", uptime);
        printf("Kernel Version: %s\n", kernelVersion);

        return 0;
    }

    // GTK GUI initialization
    gtk_init(&argc, &argv);

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "System Information");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create vertical box container
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create labels to display information
    GtkWidget *cpuLabel = gtk_label_new(NULL);
    GtkWidget *gpuLabel = gtk_label_new(NULL);
    GtkWidget *ramLabel = gtk_label_new(NULL);
    GtkWidget *uptimeLabel = gtk_label_new(NULL);
    GtkWidget *kernelLabel = gtk_label_new(NULL);

    // Get system information
    getCPUInfo(cpuInfo);
    getGPUInfo(gpuInfo);
    getRAMInfo(ramInfo);
    getUptime(uptime);
    getKernelVersion(kernelVersion);

    // Set text for labels
    gtk_label_set_text(GTK_LABEL(cpuLabel), cpuInfo);
    gtk_label_set_text(GTK_LABEL(gpuLabel), gpuInfo);
    gtk_label_set_text(GTK_LABEL(ramLabel), ramInfo);
    gtk_label_set_text(GTK_LABEL(uptimeLabel), uptime);
    gtk_label_set_text(GTK_LABEL(kernelLabel), kernelVersion);

    // Add labels to vertical box container
    gtk_box_pack_start(GTK_BOX(vbox), cpuLabel, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), gpuLabel, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), ramLabel, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), uptimeLabel, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), kernelLabel, TRUE, TRUE, 0);

    // Create close button
    GtkWidget *closeButton = gtk_button_new_with_label("Close");
    g_signal_connect(closeButton, "clicked", G_CALLBACK(on_close_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), closeButton, FALSE, FALSE, 0);

    // Show all widgets
    gtk_widget_show_all(window);

    // Run GTK main loop
    gtk_main();

    return 0;
}
