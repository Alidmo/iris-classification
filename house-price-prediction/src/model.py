from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler

def train_model(X, y, test_size=0.37, random_state=42):
    """
    Split into train/test, scale features, fit LinearRegression.
    Returns fitted Pipeline.
    """
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=test_size, random_state=random_state
    )
    pipeline = Pipeline([
        ('scaler', StandardScaler()),
        ('lr', LinearRegression())
    ])
    pipeline.fit(X_train, y_train)
    return pipeline

def predict(model, X_new):
    """
    Given fitted pipeline and new features, return predictions array.
    """
    return model.predict(X_new)
