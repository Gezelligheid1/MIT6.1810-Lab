// Mutual exclusion lock.
struct spinlock
{
    uint locked;       // Is the lock held?

    // For debugging:
    char *name;        // Name of lock.
    struct cpu *cpu;   // The cpu holding the lock.
};
struct ref_count
{
    struct spinlock lock;
    int cnt[128 * 1024 * 1024 / 4096];
};

extern struct ref_count ref;
