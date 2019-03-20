struct SplayNode {
    int key, sum;
    SplayNode *left, *right;

    SplayNode (int _v) {
        key = _v;
        left = right = NULL;
    }

    int getSum (SplayNode *x) {
        if (x == NULL) return 0;
        return x->sum;
    }

    void recalc() {
        this->sum = getSum(this->left) + getSum(this->right);
    }
};

struct SplayTree {
    SplayNode *root;

    SplayTree() {
        root = NULL;
    }

    SplayNode* rightRotate (SplayNode *now) {
        if (now == NULL) return now;

        SplayNode* ret = now->left;
        now->left = ret->right;
        ret->right = now;

        now->recalc();
        ret->recalc();

        return ret;
    }

    SplayNode* leftRotate (SplayNode *now) {
        if (now == NULL) return now;

        SplayNode* ret = now->right;
        now->right = ret->left;
        ret->left = now;

        now->recalc();
        ret->recalc();

        return ret;
    }

    SplayNode* splay (SplayNode *now, int x) {
        if (now->key == x) return now;
        
        if (now->key > x) {
            if (now->left == NULL) return now;

            if (now->left->key > x) {
                if (now->left->left == NULL) 
                    return rightRotate(now);

                now->left->left = splay(now->left->left, x);
                now = rightRotate(now);
                return rightRotate(now);

            } else if (now->left->key < x) {
                if (now->left->right == NULL) 
                    return rightRotate(now);
                
                now->left->right = splay(now->left->right, x);
                now->left = leftRotate(now->left);
                return rightRotate(now);

            } else {
                return rightRotate(now);
            }

        } else { // goto right
            if (now->right == NULL) return now;

            if (now->right->key > x) {
                if (now->right->left == NULL) 
                    return leftRotate(now);

                now->right->left = splay(now->right->left, x);
                now->right = rightRotate(now->right);
                return leftRotate(now);

            } else if (now->right->key < x) {
                if (now->right->right == NULL)
                    return leftRotate(now);

                now->right->right = splay(now->right->right, x);
                now = leftRotate(now);
                return leftRotate(now);

            } else {
                return leftRotate(now);
            }
        }
    }

    void splay (int x) {
        root = splay(root, x);
    }
};