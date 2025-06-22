# src/model.py
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler

def train_model(X, y, test_size=0.2, random_state=42):
    """
    Split data, build a pipeline (scaler + logistic reg), and fit.
    Returns the fitted Pipeline.
    """
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=test_size, stratify=y, random_state=random_state
    )
    pipe = Pipeline([
        ('scaler', StandardScaler()),
        ('clf', LogisticRegression(multi_class='auto', solver='lbfgs', max_iter=200))
    ])
    pipe.fit(X_train, y_train)
    return pipe

def predict(model, X):
    """Return class predictions for X."""
    return model.predict(X)
