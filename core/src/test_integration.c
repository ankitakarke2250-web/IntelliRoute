/*
 * Test Integration Program
 * Simple C program to test C-Flask integration
 * Outputs JSON for easy parsing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Output JSON response
    printf("{\n");
    printf("  \"success\": true,\n");
    printf("  \"message\": \"C program executed successfully\",\n");
    printf("  \"data\": {\n");
    printf("    \"compiler\": \"GCC\",\n");
    printf("    \"test\": \"integration\",\n");
    printf("    \"timestamp\": \"test-run\"\n");
    printf("  }\n");
    printf("}\n");

    return 0;
}
