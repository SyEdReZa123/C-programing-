#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_valid_email(const char email[]) {
    int at_count = 0;
    const char *at_ptr = strchr(email, '@'); // Find '@'

    if (!at_ptr || strchr(at_ptr + 1, '@')) {
        return 0; // Must have exactly one '@'
    }

    // Split local and domain
    char local_part[500], domain[500];
    if (sscanf(email, "%499[^@]@%499s", local_part, domain) != 2) {
        return 0; // Invalid if local or domain part is missing
    }

    // Local part validation
    int i;
    for (i = 0; local_part[i] != '\0'; i++) {
        if (!isalnum(local_part[i]) && local_part[i] != '.' &&
            local_part[i] != '-' && local_part[i] != '_') {
            return 0;
        }
    }

    // Domain validation
    int dot_found = 0;
    int len = strlen(domain);
    if (domain[0] == '.' || domain[len - 1] == '.') {
        return 0; // Domain should not start or end with a dot
    }

    for (i = 0; domain[i] != '\0'; i++) {
        if (!isalnum(domain[i]) && domain[i] != '.') {
            return 0;
        }
        if (domain[i] == '.') {
            dot_found = 1;
        }
    }

    return dot_found;
}

int is_valid_web_address(const char web[]) {
    if (strncmp(web, "www.", 4) != 0) {
        return 0; // Must start with "www."
    }

    const char *rest = web + 4;
    int len = strlen(rest);
    if (len == 0 || rest[0] == '.' || rest[len - 1] == '.') {
        return 0; // Invalid if empty, starts, or ends with '.'
    }

    int i;
    for (i = 0; rest[i] != '\0'; i++) {
        if (!isalnum(rest[i]) && rest[i] != '.' && rest[i] != '-') {
            return 0;
        }
    }

    return 1; // Valid web address
}

int main() {
    int n;
    printf("Enter Email or Web:\n");
    scanf("%d", &n);
    getchar(); // Consume newline

    int i;
    for (i = 1; i <= n; i++) {
        char input[1000];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline

        if (is_valid_email(input)) {
            printf("valid Email, %d\n", i);
        } else if (is_valid_web_address(input)) {
            printf("valid Web, %d\n", i);
        } else {
            printf("Invalid, %d\n", i);
        }
    }

    return 0;
}
