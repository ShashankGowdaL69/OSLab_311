#include <stdio.h>

int main() {
	int n, m, i, j, k;
	printf("Enter the number of processes and resources : ");
	scanf("%d %d", &n, &m);

	int allo[n][m], max[n][m], need[n][m], avail[m];
	printf("Enter the allo matrix:\n");
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			scanf("%d", &allo[i][j]);

	printf("Enter the maximum demand matrix:\n");
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++) {
			scanf("%d", &max[i][j]);
			need[i][j] = max[i][j] - allo[i][j];
		}

	printf("Enter the avail resources:\n");
	for (i = 0; i < m; i++)
		scanf("%d", &avail[i]);

	int finished[n], safeSequence[n], count = 0;
	for (i = 0; i < n; i++) finished[i] = 0;

	while (count < n) {
		int found = 0;
		for (i = 0; i < n; i++) {
			if (!finished[i]) {
				for (j = 0; j < m; j++)
					if (need[i][j] > avail[j]) break;
				if (j == m) {
					for (k = 0; k < m; k++)
						avail[k] += allo[i][k];
					safeSequence[count++] = i;
					finished[i] = 1;
					found = 1;
				}
			}
		}
		if (!found) {
			printf("System is in an unsafe state.\n");
			return 0;
		}
	}

	printf("System is in a safe state.\nSafe sequence: ");
	for (i = 0; i < n; i++) printf("%d ", safeSequence[i]);
	printf("\n");
	return 0;
}