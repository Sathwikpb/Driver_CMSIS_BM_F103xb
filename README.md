# Git & GitHub Commands Guide

This README provides a step-by-step guide to essential Git and GitHub commands for cloning, modifying, branching, pushing, merging, and resolving conflicts.

---

## 1️⃣ Clone a Repository
Cloning a repository creates a local copy of the project from GitHub.
```sh
# Clone a GitHub repository
git clone https://github.com/USERNAME/REPO_NAME.git
```

---

## 2️⃣ Make Changes and Push to GitHub
After modifying files, commit and push the changes to the remote repository.
```sh
# Navigate to the cloned repository
cd REPO_NAME

# Check the status of your repository
git status

# Stage modified files for commit
git add .

# Commit the changes with a message
git commit -m "Your commit message"

# Push changes to GitHub
git push origin main
```

---

## 3️⃣ Clone, Modify, and Push to a New Branch
```sh
# Clone the repository
git clone https://github.com/USERNAME/REPO_NAME.git

# Navigate into the repository
cd REPO_NAME

# Create and switch to a new branch
git checkout -b BRANCH_NAME

# Make changes, then stage and commit them
git add .
git commit -m "Added new feature"

# Push the new branch to GitHub
git push origin BRANCH_NAME
```

---

## 4️⃣ Merge a Branch into Main
```sh
# Switch to the main branch
git checkout main

# Fetch the latest changes from remote
git pull origin main

# Merge the feature branch into main
git merge BRANCH_NAME

# Push the merged changes to GitHub
git push origin main
```

---

## 5️⃣ Handling Merge Conflicts
When merging, Git may detect conflicting changes. Resolve them as follows:
```sh
# Switch to the main branch
git checkout main

# Pull latest changes
git pull origin main

# Merge the branch
git merge BRANCH_NAME
```
👉 If there are conflicts:
- Open the conflicted files.
- Manually edit and resolve the conflicts.
- After resolving, run:
  ```sh
  git add .
  git commit -m "Resolved merge conflicts"
  git push origin main
  ```

---

## 6️⃣ Delete a Branch After Merging
```sh
# Delete branch locally
git branch -d BRANCH_NAME

# Delete branch from GitHub
git push origin --delete BRANCH_NAME
```

---

## 7️⃣ Fetch and Sync with Remote Repository
```sh
# Fetch changes from GitHub
git fetch origin

# Pull latest changes and rebase
git pull --rebase origin main
```

